# Ta-Te-Ti con IA (Tic-Tac-Toe)

Este proyecto es un juego de Ta-Te-Ti donde el jugador humano compite contra una inteligencia artificial básica.

# Requisitos previos para instalar curl en su sistema
   
1. Tener un sistema operativo compatible. Pueden ser Windows, Linux (Ubuntu, Debian, Fedora, Arch, etc.) o macOS.
2.  Tener acceso como administrador.
         ¿Cómo proporcionar acceso de administrador según el sistema?
         -Windows
            Si descargás el instalador:
                  a. Hacé clic derecho sobre el archivo ejecutable.
                  b. Elegí “Ejecutar como administrador”.
         -Linux
             Usá el comando sudo para ejecutar acciones como administrador: sudo apt install curl
             Si no tenés permisos de sudo, necesitás:
                                                 Que un administrador te agregue al grupo sudo.
                                                 Usar su si tenés la contraseña del usuario root:   su
                                                                                                    apt install curl
        -macOS
          Usá sudo igual que en Linux: sudo brew install curl
          El sistema te pedirá tu contraseña de usuario si tiene privilegios de administrador.
          Si tu usuario no es administrador, necesitás uno que lo sea para instalar software.
3. Conexión a internet: Necesaria para descargar e instalar curl desde los repositorios o la web oficial.

# Instrucciones para instalar curl en su sistema operativo:
   
-Windows
   Desde Windows 10 en adelante, curl ya viene preinstalado.
   Para verificarlo: Abrí CMD escribiendo "cmd" en el buscador de windows y ejecutá: curl --version
   Si no está:
      a.Descargá el instalador desde: https://curl.se/windows/ según los bits de tu sistema.
      b.Descomprimí el ZIP. Clic derecho sobre el archivo, "Extraer todo".
      c. Mové esa carpeta a un lugar fácil, por ejemplo: C:\Program Files\curl\
      d.Ahora vas a decirle a Windows dónde está curl para que puedas usarlo desde cualquier lugar:
         -Hacé clic en el botón de Inicio y buscá: variables de entorno
         -En la ventana que aparece, hacé clic en el botón que dice "Variables de entorno..." (abajo a la derecha).
         -En la parte que dice "Variables del sistema", buscá una llamada Path.
         -Seleccionala y hacé clic en "Editar...".
         -En la nueva ventana, hacé clic en "Nuevo", y pegá la ruta donde pusiste curl. Por ejemplo: C:\Program Files\curl\
         -Hacé clic en Aceptar en todas las ventanas para guardar los cambios.
         -Cerrá y volvé a abrir la ventana de comandos (CMD).
         -Escribí: curl --version
         
-Linux
   a. Abrí una terminal.
   b. Ejecutá: sudo apt update
               sudo apt install curl
   c. Verificá que se instaló correctamente escribiendo: curl --version y presioná enter.

-macOS
   curl viene preinstalado con macOS.
   Para actualizarlo o reinstalarlo, usá Homebrew: brew install curl

## 🎮 ¿Cómo jugar?

1. Ejecutá el programa.
2. Elegí una opción del menú:
   - 1) Jugar: comienza una nueva partida contra la IA.
   - 2) Ver ranking de equipo: aparece un listado con los nombres de los jugadores y su respectiva puntuación obtenida.
   - 3) Salir: cierra el juego.
3. Durante el juego, seleccioná una casilla del 1 al 9 según el tablero con guías.
4. El objetivo es formar una línea de 3 fichas (vertical, horizontal o diagonal) antes que la IA.

# Configurar el juego

1. Abrir la carpeta del juego.
2. Abrir el archivo "config".
3. Cambiar por el número de partidas que quiere jugar.
4. Disfrute :).
