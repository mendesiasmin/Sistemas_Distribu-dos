1 - O primeiro passo para configuração do ambiente de desenvolvimento, é a instalação das dependências abaixo

### Instalar Virtual Box
`sudo apt-get install virtualbox`

### Instalar Vagrant
Baixe o vagrant no seguinte link:

[vagrant](https://www.vagrantup.com/downloads.html)

(Para ubuntu use a Debian 64)


### Instalar recursos de virtualização para o Virtual Box
`sudo apt-get install virtualbox-dkms`

### Instalar ruby e rubygem-library
`sudo apt-get install ruby-full`

### Instalar chake
`sudo gem install chake`

### Baixar debian box para o vagrant
`vagrant box add debian/jessie64`

### Instalar vbguest plugin
`vagrant plugin install vagrant-vbguest`

> **Uma vez que as dependências acima foram corretamente instaladas, execute os comandos abaixo:**

### Clone o repositório e entre na pasta chef-devenv
`git clone https://github.com/PlataformaJogosUnB/chef-devenv.git`

### Subir a Máquina Virtual
> Dentro da pasta do repositório, onde está o VagrantFile, rode o comando para subir a VM:

`vagrant up`

### Verificar se já possui chave pública
`cat ~/.ssh/id_rsa.pub`

### Caso o arquivo `id_rsa.pub` não exista, rodar keygen para gerar a chave publica
`ssh-keygen`

### Antes de rodar a receita dentro da máquina é necessário copiar a chave pública para dentro da VM. Abaixo seguem duas formas de fazê-lo, caso a primeira forma não funcione siga os passo da segunda forma.

### Método 1 - OBS: Quando o comando for executado será solicitada a senha do user vagrant, digitar a senha: vagrant
`ssh-copy-id -i ~/.ssh/id_rsa.pub vagrant@10.10.10.11`

### Método 2 - Copie a chave pública que está no arquivo ~/.ssh/id_rsa.pub. Usar o comando abaixo para exibir a chave pública.
`cat ~/.ssh/id_rsa.pub`

### Entrar na VM com o comando abaixo:
`vagrant ssh`

### Dentro da VM, cole a chave copiada no arquivo ~/.ssh/authorized_keys. Caso o arquivo não exista deve-se criar o arquivo dentro da pasta ~/.ssh

### Saia da VM, e dentro da pasta onde está o Vagrantfile execute o comando abaixo, que roda as receitas para configuração do ambiente de desenvolvimento dentro da VM

`rake converge:devenv`
