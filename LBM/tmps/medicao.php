<?php
    $diretorio = "../dados/";
    $arquivos = scandir($diretorio);
    $arquivos = array_diff($arquivos, array(".", "..", date("Y-m-d").".json"));
?>
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Lab+</title>
        <link rel="stylesheet" href="../static/css/index.css">
        <link rel="stylesheet" href="../static/css/medicao.css">
        <link rel="stylesheet" href="../static/css/bootstrap.min.css">
    </head>
    <body>
        <main class="d-flex flex-column flex-md-row">
            <div id="esquerda" class="d-flex flex-row flex-md-column">
                <img src="../static/imgs/Capturar.PNG" alt="" id="logo">
                <p class="d-none d-md-flex" id="saudacao">Ola, ADM</p>
                
                <div id="nav" class="d-flex flex-row flex-md-column">
                    <button id="inicio_lnk" > <img src="../static/imgs/home.png"> <txt class="d-none d-md-flex">Inicio</txt> </button>
                    <button id="documentos_lnk"> <img src="../static/imgs/doc.png"> <txt class="d-none d-md-flex">Documentos</txt> </button>
                    <button id="medicoes_lnk"> <img src="../static/imgs/medicoes.png"> <txt class="d-none d-md-flex">Medições</txt> </button>
                    <button id="suporte_lnk"> <img src="../static/imgs/suporte.png"> <txt class="d-none d-md-flex">Suporte</txt> </button>
                </div>
            </div>
            <div id="direita">
                <!-- conteudo -->
                <h1>Medições</h1><br>
                <div id="med_data" class="d-flex">
                    SELECIONE A DATA:
                    <select name="" id="med_data_select">
                        <option value="0">Hoje</option>
                        <?php foreach ($arquivos as $arquivo) {
                            $data = str_replace(".json", "", $arquivo);
                            echo "<option value='".$data."'>".$data."</option>";
                        } ?>
                    </select>
                </div><br>
                    <div id="med_graf">
                        <div id="med_graf_titulo">
                            TEMPERATURA X UMIDADE
                        </div>
                        <div id="med_graf_graficos">
                            <div id="med_graf_esquerda">
                                <canvas id="med_graf_canvas"></canvas>
                            </div>
                        </div>
                    </div>
                </div>
                <!-- conteudo -->
        </main>
    </body>
    <script src="../static/js/config.js"></script>
    <script src="../static/js/nav.js"></script>
    <script src="../static/js/chart.js"></script>
    <script src="../static/js/medicao.js"></script>
</html>