const linhas_tmp = document.getElementById("med_graf_canvas");
const data_select = document.getElementById("med_data_select");
med_lnk.focus();
//cria o gráfico
const grafico_tmp_linhas = new Chart(linhas_tmp, {
    type: 'line',
    data: {
        labels: ["1"],
        datasets: [{
            label: "Temperatura",
            data: [],
            borderColor: 'red'
        },
        {
            label: "Umidade",
            data: [],
            borderColor: "blue"
        }],
        options: {
            responsive: true,
            maintainAspectRatio: false,
            plugins: {
                legend: {
                    display: false
                }
            }
        }
    }
});

//busca todos os dados
fetch(MAIN_URL + "/scripts/envio_meds.php", {
    method : "GET"
}).then(r => { return r.json()}).then(dados => {

    const labels = dados.map(item => item.dia);
    const tmps = dados.map(item => item.tmp);
    const umds = dados.map(item => item.umd);
    grafico_tmp_linhas.data.labels = labels;
    grafico_tmp_linhas.data.datasets[0].data = tmps;
    grafico_tmp_linhas.data.datasets[1].data = umds;
    grafico_tmp_linhas.update();
})
//busca os atuais
const intervalo = setInterval( () => {

    fetch(MAIN_URL + "/scripts/envio_ultima_med.php", {
    method : "GET"
}).then(r => {  return r.json() }).then(dados => {

    grafico_tmp_linhas.data.labels.push(dados.dia);
    grafico_tmp_linhas.data.datasets[0].data.push(dados.tmp);
    grafico_tmp_linhas.data.datasets[1].data.push(dados.umd);
    grafico_tmp_linhas.update();
    

})

}, TEMPO_REQ_MEDIDAS );







