<?php
    $arquivo = 'invasoes.json';
    $novoHorario = json_decode(file_get_contents('php://input'), true);
    $horarios = [];
    if (file_exists($arquivo)) {
        $horarios = json_decode(file_get_contents($arquivo), true);
    }
    $horarios[] = $novoHorario;
    file_put_contents(
        $arquivo,
        json_encode($horarios, JSON_PRETTY_PRINT)
    );
    echo 'OK';
?>