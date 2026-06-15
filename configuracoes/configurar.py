from pathlib import Path
import os

#Nginx
conteudo_nginx = """
server{
	listen 80;
	server_name lab_m;

	root /var/www/html/LBM;
	index tmp/index.html;
    }

"""
#confere arquivo de configuração
nginx_conf = Path("/etc/nginx/sites-enabled/default")
if nginx_conf.exists():
    nginx_conf.write_text(conteudo_nginx)
    print("nginx configurado")
else:
    print("ERRO: configuracao do nginx nao encontrada")
#confere diretorio servido
diretorio = Path("/var/www/html/LBM")
arquivo = diretorio / "tmp" / "index.html"
if arquivo.exists():
    print("arquivo servido encontrado com sucesso em /var/www/html/LBM/tmp/index.html")
else:
    print("AVISO: o caminho servido pelo nginx não possui arquivos html ou php")

#NAS
conteudo_msg_teste = "ola Camila, sou um arquivo de testes, se você está me vendo, então o NAS está funcionando =)"
conteudo_NAS = """
[global]
    workgroup = WORKGROUP
    server string = Samba Server
    security = user
    map to guest = bad user
    dns proxy = no

    server min protocol = SMB2

[NAS]
    path = /var/Pasta_compartilhada_LAB+
    browseable = yes
    writeable = yes
    guest ok = yes
    read only = no
    force user = nobody
"""
#checa arquivo de configuração
NAS_conf = Path("/etc/samba/smb.conf")
if NAS_conf.exists():
    NAS_conf.write_text(conteudo_NAS)
    print("NAS configurado")
else:
    print("ERRO: falha ao configurar o servidor NAS")
#cria pasta compartilhada
caminho_pasta_compartilhada = Path("/var/Pasta_compartilhada_LAB+")
if caminho_pasta_compartilhada.exists() and caminho_pasta_compartilhada.is_dir():
    print("pasta compartilhada encontrada")
else:
    caminho_pasta_compartilhada.mkdir(parents=True, exist_ok=True)
    caminho_pasta_compartilhada.chmod(0o777)
    print("pasta compartilhada não encontrada, criada com sucesso")
    arq_test = caminho_pasta_compartilhada / "me_leia.txt"
    arq_test.write_text(conteudo_msg_teste)
    
print("\n CHECAGEM CONCLUIDA")
try:
    os.system("systemctl restart nginx")
    os.system("systemctl restart smbd")
except:
    print("reinicie o Nginx e o NAS")