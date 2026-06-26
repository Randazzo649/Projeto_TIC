async function carregarInvasoes() {

    const resposta = await fetch(MAIN_URL + "scripts/invasoes.php");
    const invasoes = await resposta.json();
    const tabela = document.getElementById("tabela");
    tabela.innerHTML = "";
    invasoes.forEach(invasao => {
        const status = invasao.verificado
            ? '<span class="verificado">Verificado</span>'
            : `<button class="btn btn-danger" onclick="verificarInvasao(${invasao.id})">
                    Verificar
               </button>`;
        tabela.innerHTML += `
            <tr>
                <td>${invasao.data_movimento}</td>
                <td>${status}</td>
            </tr>
        `;
    });
}

async function verificarInvasao(id){
    await fetch(MAIN_URL + "scripts/verificar_alerta.php",{
        method:"POST",
        headers:{
            "Content-Type":"application/json"
        },
        body: JSON.stringify({
            id:id
        })
    });
    carregarInvasoes();
}

carregarInvasoes();