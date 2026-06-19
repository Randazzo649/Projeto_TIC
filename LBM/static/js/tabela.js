async function carregarInvasoes() {

    const resposta = await fetch(MAIN_URL + "scripts/invasoes.php", {
        method: "POST"
    });

    const invasoes = await resposta.json();

    const tabela = document.getElementById("tabela");

    tabela.innerHTML = "";

    invasoes.forEach(invasao => {

        const status = invasao.verificado ? '<span class="verificado">Verificado</span>' : 
            `<a href="${MAIN_URL}scripts/verificar_alerta.php?id=${invasao.id}">
                Não verificado
            </a>`;

        tabela.innerHTML += `
            <tr>
                <td>${invasao.data_movimento}</td>
                <td>${status}</td>
            </tr>
        `;
    });
}

carregarInvasoes();