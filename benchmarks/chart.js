"use strict";

const fs = require("fs");
const path = require("path");
const fastify = require("fastify")({ logger: true });

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

const scriptFunction = getScriptFunction({
  data: data.OrdD,
  title: "Vetores Aleatórios",
  id: "OrdD"
});
const html = generateHtml(scriptFunction);

fastify.get("/", async (req, res) => {
  res.header("Content-Type", "text/html").send(html);
});

const start = async () => {
  try {
    await fastify.listen(3000);
    fastify.log.info(`server listening on ${fastify.server.address().port}`);
  } catch (err) {
    fastify.log.error(err);
    process.exit(1);
  }
};
start();

function generateHtml(scriptFunction) {
  return `<!DOCTYPE html>
<html>
  <head>
    <title></title>
    <meta charset="utf-8" />
      <script src="https://cdn.jsdelivr.net/npm/chart.js@2.8.0"></script>
    <style></style>
  </head>
  <body>
    <canvas id="Ale"></canvas>
    <canvas id="OrdC"></canvas>
    <canvas id="OrdD"></canvas>
    <script>
      ${scriptFunction}
    </script>
  </body>
</html>
`;
}

function getScriptFunction({ data, title, id }) {
  const datasets = [
    { variation: "QC", color: "green" },
    { variation: "QPE", color: "red" },
    { variation: "QM3", color: "blue" },
    { variation: "QI1", color: "yellow" },
    { variation: "QI5", color: "purple" },
    { variation: "QI10", color: "brown" },
    { variation: "QNR", color: "orange" }
  ];
  return ` 
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
          data: data[variation]
        }))
      )}
    },
    options: {
      title: {
        display: true,
        text: "${title}"
      }
    }
  });
`;
}

function getChartData(objs) {
  return objs.reduce(
    (chartData, { type, variation, time }) => {
      if (!Array.isArray(chartData[type][variation])) {
        chartData[type][variation] = [];
      }
      chartData[type][variation].push(time / Math.pow(10, 6));
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

// const file = "ola;mundo\npapai;noel\n";
// const labels = ["inicial", "secundario"];

// console.log(csvParser({ file, labels, delimiter: ";" }));
