function RenderChart(ch, data, title, unit, min = undefined, max = undefined) {
    return new Chart(ch, {
        type: "line",
        maintainAspectRatio: false,
        responsive: true,
        data: {
            labels: data.map(i => i.ts),
            datasets: [{
                data: data.map(i => i.value),
                fill: false,
                borderColor: 'rgb(75, 192, 192)',
                tension: 0.125
            }]
        },
        options: {
            scales: {
                x: {
                    type: 'time',
                    time: {
                        unit: 'hour'
                    },
                    title: {
                        display: true,
                        text: 'Time'
                    }
                },
                y: {
                    display: true,
                    title: {
                        display: true,
                        text: title
                    },
                    min: min,
                    max: max,
                    ticks: {
                        callback: (value, index, values) => value + unit
                    }
                }
            },
            tooltips: {
                callbacks: {
                    label: value => value + unit
                }
            },
            plugins: {
                legend: {
                    display: false
                }
            }
        }
    });
}

