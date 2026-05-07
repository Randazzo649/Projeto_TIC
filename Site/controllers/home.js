fetch("/arquivos/")
.then(res => res.text())
.then(html => {
    const parser = new DOMParser();
    const doc = parser.parseFromString(html, "text/html");
    const links = doc.querySelectorAll("a");
    const tabela = document.getElementById("tabela");
    tabela.innerHTML = "";
    links.forEach(link => {
        const nome = link.textContent;
        if(nome !== "../"){
            const linha = document.createElement("tr");
            linha.innerHTML = `<td>${nome}</td>`;
            tabela.appendChild(linha);
        }
    });
    const nomes = [];
    links.forEach(link =>{
        nome => push(link.textContent);
    });
    nomes.sort();
})

.catch(error => {
    console.error("Erro ao carregar arquivos:", error);
});