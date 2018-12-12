Лабораторная по оптимизации (все сборки под Windows). Сборка компилятором от Intel
1. Найти папку с компилятором C:\Program Files (x86)\IntelSWTools\compilers_and_libraries_2019.0.120\windows
2. В командной строке call C:\Program Files (x86)\IntelSWTools\compilers_and_libraries_2019.0.120\windows\bin\compilervars.bat" intel64 (нужно выбрать свою платформу; в моем случае - 64) - установка путей до необходимых файлов в системные переменные
3. В ком.строке- icl - поиск компилятора:
   C:\Program Files (x86)\IntelSWTools\compilers_and_libraries_2019.0.120\windows\bin\intel64\icl.exe
4. Компиляция: icl -o Example -openmp optim.cpp
   На выходе: optim.obj и Example.exe
  Ключи компиляции можно найти в оффициальной документации Intel или, например, https://habr.com/company/intel/blog/256251/
