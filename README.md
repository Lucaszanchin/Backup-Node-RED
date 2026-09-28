# 🔄 Backup Node-RED

Repositório destinado ao armazenamento e versionamento dos arquivos de **backup do Node-RED**, permitindo manter os fluxos salvos e facilitar sua recuperação em caso de perda ou necessidade de reinstalação.

## 📌 Sobre o projeto

O **Node-RED** é uma ferramenta de programação visual utilizada para conectar dispositivos, APIs, serviços e sistemas por meio de fluxos.

Este repositório tem como objetivo manter uma cópia segura dos fluxos desenvolvidos no Node-RED, utilizando o **Git/GitHub** para versionamento.

## 💾 Como realizar um backup

Antes de realizar alterações importantes no projeto, recomenda-se salvar uma cópia dos arquivos do Node-RED.

Também é possível utilizar o recurso de exportação do próprio Node-RED para salvar os fluxos em formato JSON.

## ♻️ Como restaurar o backup

Para restaurar os fluxos, copie os arquivos de backup para o diretório utilizado pelo Node-RED.

Depois, reinicie o Node-RED para que as alterações sejam carregadas.

Caso seja utilizado o arquivo `flows.json`, também é possível importar os fluxos diretamente pela interface do Node-RED.

## 🔐 Segurança

**Atenção:** arquivos de backup podem conter informações sensíveis, como:

* Senhas;
* Tokens de acesso;
* Chaves de API;
* Credenciais de serviços;
* Informações de conexão com bancos de dados.

Antes de enviar os arquivos para um repositório público, verifique se eles possuem informações confidenciais.

Se necessário, utilize um `.gitignore` para impedir o envio de arquivos sensíveis.

## 🛠️ Tecnologias

* **Node-RED**
* **Git**
* **GitHub**
* **JSON**

## 📚 Objetivo

Este repositório foi criado para:

* 💾 Manter backups dos fluxos;
* 🔄 Facilitar a restauração do Node-RED;
* 📋 Manter histórico das alterações;
* 🌐 Armazenar os arquivos de forma organizada no GitHub;
* 🛡️ Reduzir o risco de perda dos fluxos.

---

## 👨‍💻 Autor

Desenvolvido para fins de estudo, desenvolvimento e backup de projetos utilizando **Node-RED**.
