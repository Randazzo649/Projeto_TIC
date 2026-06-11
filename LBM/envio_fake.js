
const dados = new FormData();
dados.append("temperatura", "20");
dados.append("umidade", "60%");
fetch("http://127.0.0.1/IoT1/scripts/recebimento_dados.php", {
    method : "POST",
    body : dados
}).then(r => {return r.text()}).then(r => {
    console.log(r);
})