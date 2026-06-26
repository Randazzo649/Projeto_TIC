<?php
    header('Content-Type: application/json');
    date_default_timezone_set('America/Sao_Paulo');
    $arquivo = '../dados/seg/invasoes.json';
    $invasoes = [];
    $horaAtual = date('H:i');

    if ($horaAtual >= "08:00" && $horaAtual < "17:00") {
        echo json_encode([
            "status" => "HORARIO_PERMITIDO"
        ]);
        exit;
    }

    if (file_exists($arquivo)) {
        $invasoes = json_decode(file_get_contents($arquivo), true) ?? [];
    }

    foreach ($invasoes as $invasao) {
        if ($invasao['verificado'] == false) {
            echo json_encode([
                "status" => "PENDENTE"
            ]);
            exit;
        }
    }

    if ($_SERVER["REQUEST_METHOD"] === "POST") {

        $novoRegistro = [
            "id" => count($invasoes) + 1,
            "movimento" => true,
            "data_movimento" => date("Y-m-d H:i:s"),
            "verificado" => false
        ];

        $invasoes[] = $novoRegistro;

        file_put_contents($arquivo, json_encode($invasoes, JSON_PRETTY_PRINT));

        echo json_encode([
            "status" => "OK"
        ]);
        exit;
    }

    echo json_encode($invasoes);
?>