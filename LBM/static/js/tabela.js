async function carregarInvasoes() {
    const resposta = await fetch('invasoes.json');
    const invasoes = await resposta.json();

    const tabela = document.getElementById('tabela');
    tabela.innerHTML = '';

    horarios.forEach(invasao => {
        tabela.innerHTML += `
            <tr>
                <td>${invasao}</td>
            </tr>
        `;
    });
}

carregarHorarios();