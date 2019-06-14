module.exports = function(scriptFunction) {
  return `<!DOCTYPE html>
  <html>
    <head>
      <title></title>
      <meta charset="utf-8" />
      <script src="https://cdn.jsdelivr.net/npm/chart.js@2.8.0"></script>
      <style>
        .wrapper {
          text-align: center;
        }
        .charts {
          display: inline-block;
          width: 75%;
        }
        h1	{
          font-family: arial, sans-serif;
          font-size: 34px;
          font-weight: bold;
          margin-top: 10px;
          margin-bottom: 1px;
          text-decoration: underline;
        }        
        hr {
          display: block;
          height: 1px;
          border: 0;
          border-top: 1px solid #ccc;
          margin: 1em 0;
          width: 80%;
          display: inline-block;
          text-align: center;

          padding: 0;
        }
        canvas {
          background-color: white;
          margin-top: 30px;
        }
      </style>
    </head>
    <body class="container">
      <div class="wrapper">
        <div class="charts">
          <h1>Tempo de Execução</h1>
          <canvas id="timeAle"></canvas>
          <canvas id="timeOrdC"></canvas>
          <canvas id="timeOrdD"></canvas>
        </div>
        <hr/>
        <div class="charts">
          <h1>Número de Comparações</h1>
          <canvas id="nCompAle"></canvas>
          <canvas id="nCompOrdC"></canvas>
          <canvas id="nCompOrdD"></canvas>
        </div>
        <hr/>
        <div class="charts">
        <h1>Número de Movimentações</h1>
        <canvas id="nMovAle"></canvas>
        <canvas id="nMovOrdC"></canvas>
        <canvas id="nMovOrdD"></canvas>
      </div>
      </div>
      ${scriptFunction}
    </body>
  </html>
`;
};
