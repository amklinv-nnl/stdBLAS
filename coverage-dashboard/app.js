fetch("coverage.json")
  .then(r => r.json())
  .then(data => {
    const table = document.getElementById("table");

    let totalHit = 0;
    let totalLines = 0;

    data.forEach(row => {
      totalHit += row.hit;
      totalLines += row.total;

      const tr = document.createElement("tr");

      tr.innerHTML = `
        <td>${row.file}</td>
        <td>${row.coverage.toFixed(2)}%</td>
        <td>${row.hit}</td>
        <td>${row.total}</td>
      `;

      table.appendChild(tr);
    });

    const summary = document.getElementById("summary");
    const overall = (totalHit / totalLines * 100).toFixed(2);

    summary.innerHTML = `
      <h2>Overall Coverage: ${overall}%</h2>
    `;
  });