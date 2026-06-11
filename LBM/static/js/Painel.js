const IP_DO_SERVIDOR = "192.168.15.4";
const barra_tmp = document.getElementById("barraTMP");
const barra_umd = document.getElementById("barraUMD");
const displayTMP = document.getElementById("TMP");
const displayUMD = document.getElementById("UMD");
const cor = "blue";
const proporcao_tmp = 180 / 50; //50°C = 180°
const proporcao_umd = 180 / 120; //120% = 180°

setInterval( () => {

    fetch("http://"+IP_DO_SERVIDOR+"/IoT1/scripts/envio_dados.php",{
        method : "GET"
    }).then(r => {return r.json()}).then( r => {
        renderTMP(r.tmp);
        renderUMD(r.umd);
    });

}, 3000 );

//renderiza o grafico da temperatura
function renderTMP( TMP){
    const angulo = proporcao_tmp * TMP;
    barra_tmp.style.background = "conic-gradient( "+cor+" "+angulo+"deg, white 0deg";
    displayTMP.innerHTML = "Temperatura: "+TMP+"°C";
}

//reenderiza o grafico da umidade
function renderUMD( UMD ){
    const angulo = proporcao_umd * UMD;
    barra_umd.style.background = "conic-gradient( "+cor+" "+angulo+"deg, white 0deg";
    displayUMD.innerHTML = "Umidade: "+UMD+"%";
}