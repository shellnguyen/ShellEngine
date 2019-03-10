@echo start copy

xcopy "%1lib\SDL2_mixer-2.0.2\lib\%3\SDL2_mixer.dll" "%2" /y
xcopy "%1lib\SDL2_mixer-2.0.2\lib\%3\libFLAC-8.dll" "%2" /y
xcopy "%1lib\SDL2_mixer-2.0.2\lib\%3\libmodplug-1.dll" "%2" /y
xcopy "%1lib\SDL2_mixer-2.0.2\lib\%3\libmpg123-0.dll" "%2" /y
xcopy "%1lib\SDL2_mixer-2.0.2\lib\%3\libogg-0.dll" "%2" /y
xcopy "%1lib\SDL2_mixer-2.0.2\lib\%3\libvorbis-0.dll" "%2" /y
xcopy "%1lib\SDL2_mixer-2.0.2\lib\%3\libvorbisfile-3.dll" "%2" /y
xcopy "%1lib\SDL2-2.0.7\lib\%3\SDL2.dll" "%2" /y
xcopy "%1lib\Assimp-3.3.1\lib\%3\assimp-vc140-mt.dll" "%2" /y
xcopy "%1lib\glew-2.1.0\bin\Release\%3\glew32.dll" "%2" /y

@echo end copy