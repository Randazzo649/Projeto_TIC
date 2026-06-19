<?php

header('Content-Type: application/json');
$arquivo = 'invasoes.json';
$dados = json_decode(file_get_contents('php://input'), true);
if (!$dados || !isset($dados['data_movimento'])) {
    http_response_code(400);
    echo json_encode(['erro' => 'Dados inválidos']);
    exit;
}
$invasoes = [];
if (file_exists($arquivo)) {
    $invasoes = json_decode(file_get_contents($arquivo), true) ?? [];
}
$novoRegistro = [
    'id' => count($invasoes) + 1,
    'movimento' => $dados['movimento'] ?? true,
    'data_movimento' => $dados['data_movimento'],
    'verificado' => false
];
$invasoes[] = $novoRegistro;
file_put_contents(
    $arquivo,
    json_encode($invasoes, JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE)
);
echo json_encode(['status' => 'OK']);

?>