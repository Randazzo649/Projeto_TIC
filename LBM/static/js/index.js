const main_div = document.getElementById("direita");
const ini_lnk = document.getElementById("inicio_lnk");
const med_lnk = document.getElementById("medicoes_lnk");
const doc_lnk = document.getElementById("documentos-lnk");


med_lnk.onclick = () => {
    window.location.href = MAIN_URL+"/tmps/medicao.php";
}