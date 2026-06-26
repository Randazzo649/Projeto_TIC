<?php
    header('Content-Type: application/json');
    date_default_timezone_set('America/Sao_Paulo');
    $arquivo = 'invasoes.json';
    $dados = json_decode(file_get_contents('php://input'), true);

    if (!$dados || !isset($dados['movimento']) || $dados['movimento'] != true) {
        http_response_code(400);
        echo json_encode([
            "status" => "ERRO",
            "mensagem" => "Dados inválidos."
        ]);
        exit;
    }

    $horaAtual = date('H:i');

    if ($horaAtual >= "08:00" && $horaAtual < "17:00") {
        echo json_encode([
            "status" => "HORARIO_PERMITIDO"
        ]);
        exit;
    }

    $invasoes = [];

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

    $novoRegistro = [
        "id" => count($invasoes) + 1,
        "data_movimento" => date("d/m/Y H:i:s"),
        "verificado" => false
    ];

    $invasoes[] = $novoRegistro;

    file_put_contents(
        $arquivo,
        json_encode($invasoes, JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE)
    );

    echo json_encode([
        "status" => "OK"
    ]);
?>