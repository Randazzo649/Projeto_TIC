<?php


    if($_SERVER["REQUEST_METHOD"] == "POST"){

        // obtem os dados antigos
        $arquivo = "../dados/" . date("Y-m-d") . ".json";
        $dados = [];
        if (file_exists($arquivo)) {
            $conteudo = file_get_contents($arquivo);
            $dados = json_decode($conteudo, true);
            //para o caso de o json estar vazio
            if (!is_array($dados)) {
                $dados = [];
            }
        }
        //salva a nova medição
        $novaLeitura = [
            "dia" => date("H:i:s"),
            "tmp" => floatval($_POST["temp"]),
            "umd" => floatval($_POST["umid"])
        ];
        $dados[] = $novaLeitura;
        // salva de volta
        file_put_contents($arquivo, json_encode($dados, JSON_PRETTY_PRINT));        

        echo "ok";
    }


?>