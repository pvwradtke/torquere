mkdir c:\temp\torquere\audio\
mkdir c:\temp\torquere\fases\
mkdir c:\temp\torquere\imagens\
mkdir c:\temp\torquere\menu\
mkdir c:\temp\torquere\musicas\

copy audio\*.* c:\temp\torquere\audio\
copy fases\*.* c:\temp\torquere\fases\
copy imagens\*.* c:\temp\torquere\imagens\
copy menu\*.* c:\temp\torquere\menu\
copy musicas\*.* c:\temp\torquere\musicas\
copy visual\release\tocha.exe c:\temp\torquere\torquere.exe

copy %SDL_HOME%\lib\*.dll      c:\temp\torquere\
copy %SDL_IMAGE_HOME%\lib\*.dll        c:\temp\torquere\
copy %SDL_MIXER_HOME%\lib\*.dll          c:\temp\torquere\

                        

