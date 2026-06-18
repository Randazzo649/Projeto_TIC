<?php
    $arquivo = "../dados/".date("Y-m-d").".json";

    if($_SERVER["REQUEST_METHOD"] == "GET"){

        $dados = json_decode(file_get_contents($arquivo, true));

        header("Content-Type: application/json");
        echo json_encode($dados);

    }

?>