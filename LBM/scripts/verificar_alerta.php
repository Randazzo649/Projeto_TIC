<?php
    header('Content-Type: application/json');
    $arquivo = 'invasoes.json';
    $dados = json_decode(file_get_contents("php://input"), true);
    $id = $dados["id"] ?? 0;
    $invasoes = json_decode(file_get_contents($arquivo), true) ?? [];

    foreach($invasoes as &$invasao){
        if($invasao["id"] == $id){
            $invasao["verificado"] = true;
            break;
        }
    }

    file_put_contents(
        $arquivo,
        json_encode($invasoes, JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE)
    );

    echo json_encode([
        "status"=>"OK"
    ]);
?>