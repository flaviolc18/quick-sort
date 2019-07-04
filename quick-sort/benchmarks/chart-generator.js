"use strict";

const fs = require("fs");
const path = require("path");
const generateHtml = require("./html-generator");

const FILENAME = "benchmark.csv";
const DELIMITER = ";";

const file = fs.readFileSync(path.join(__dirname, FILENAME), "utf8", err => {
  if (err) throw err;
});

const labels = {
  variation: "Variação",
  type: "Tipo",
  size: "Tamanho",
  nComp: "Comparações",
  nMov: "Movimentações",
  time: "Tempo Execução"
};

const parsedFile = csvParser({
  file,
  labels: Object.keys(labels),
  delimiter: DELIMITER
});

const data = getChartData(parsedFile);

const metrics = ["time", "nComp", "nMov"];

const scriptFunctions = [].concat.apply(
  [],
  metrics.map(metric => [
    getScriptFunction({
      data: data.Ale,
      title: "Vetores Aleatórios",
      id: `${metric}Ale`,
      metric
    }),
    getScriptFunction({
      data: data.OrdC,
      title: "Vetores Crescentes",
      id: `${metric}OrdC`,
      metric
    }),
    getScriptFunction({
      data: data.OrdD,
      title: "Vetores Decrescentes",
      id: `${metric}OrdD`,
      metric
    })
  ])
);
const html = generateHtml(scriptFunctions.join(""));

fs.writeFile(path.join(__dirname, "chart.html"), html, err => {
  if (err) throw err;
});

function getScriptFunction({ data, title, id, metric }) {
  const datasets = [
    { variation: "QC", color: "#469990" },
    { variation: "QPE", color: "#e6194B" },
    { variation: "QM3", color: "#9A6324" },
    { variation: "QI1", color: "#3cb44b" },
    { variation: "QI5", color: "#4363d8" },
    { variation: "QI10", color: "#aaffc3" },
    { variation: "QNR", color: "#911eb4" }
  ];
  return ` 
  <script>
    var ctx = document.getElementById("${id}").getContext("2d");
    var chart = new Chart(ctx, {
      type: "bar",
      data: {
        labels: [
          50000,
          100000,
          150000,
          200000,
          250000,
          300000,
          350000,
          400000,
          450000,
          500000
        ],
        datasets: ${JSON.stringify(
          datasets.map(({ variation, color }) => ({
            label: variation,
            backgroundColor: color,
            data: data[variation].map(metrics => metrics[metric])
          }))
        )}
      },
      options: {
        responsive: true,
        title: {
          display: true,
          text: "${title}",
          fontSize: 26,
          color: "#999999"
        },
        scales: {
          xAxes: [{
              categoryPercentage: 0.6,
              barPercentage: 0.8,
          }],
          yAxes: [{
            minBarLength: 2,
            ticks: {
              beginAtZero:true,
          }
        }]
        }
      }
    });
  </script>  
`;
}

function getChartData(objs) {
  return objs.reduce(
    (chartData, { type, variation, time, nComp, nMov }) => {
      if (!Array.isArray(chartData[type][variation])) {
        chartData[type][variation] = [];
      }
      chartData[type][variation].push({
        time: time / Math.pow(10, 6),
        nComp,
        nMov
      });
      return chartData;
    },
    { Ale: {}, OrdC: {}, OrdD: {} }
  );
}

function csvParser({ labels, file, delimiter }) {
  return file
    .split("\n")
    .filter(l => l)
    .reduce((parsedObjs, line) => {
      const elems = line.split(delimiter);
      const parsedObj = labels.reduce((obj, column, index) => {
        obj[column] = elems[index];
        return obj;
      }, {});
      parsedObjs.push(parsedObj);
      return parsedObjs;
    }, []);
}
