# Discord RPC Apple Music

Este projeto integra a reprodução de música do Apple Music com o Discord, utilizando a **Discord Rich Presence**. Ele permite que o nome da música, artista e álbum sejam exibidos diretamente no seu perfil do Discord.

**IMPORTANTE:**
**Nota:** O projeto ainda não filtra outras fontes de áudio (como YouTube, por exemplo), portanto, pode exibir informações de reprodução de outras mídias, além do Apple Music.
**Motivo:** O SDK do windows é um pouco delicado de mexer, e estou pesquisando como ancorar o aplicativo no apple music, acessando pelo pid e evitando exibir as informações de outros apps, atualmente ele usa o Windows::Media pra pegar os dados já que apple não facilita nem um pouco a criação de apis.

## Funcionalidades

- Exibe a música, artista e álbum atualmente em reprodução no Apple Music.
- Mostra a imagem da capa do álbum diretamente no Discord, atualmente não funciona pois preciso descobrir como puxar imagens on the fly usando o nome da música e procurar em alguma cdn que guarde as imagens e capas, e o discord não deixa usar um stream de dados como imagem nem a imagem salva...
- Atualiza as informações a cada segundo (não altera performance, é feito em c++....) enquanto a música estiver tocando.

## Requisitos

- **Windows 10 ou superior**
- **Visual Studio 2019 ou superior** com suporte a C++17 ou superior
- **Discord**: Conta configurada para mostrar as atividades no perfil.

## Como compilar o projeto

1. **Clone o repositório:**

   Se você ainda não fez isso, clone o repositório com o seguinte comando:

   ```bash
   git clone https://seu-repositorio.git
