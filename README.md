## Сборка и запуск

### Предварительные требования
Убедитесь, что установлены следующие библиотеки:

```bash
# Для Ubuntu/Debian
sudo apt-get install libsdl2-dev libsdl2-ttf-dev

# Для Arch Linux
sudo pacman -S sdl2 sdl2_ttf

# Для macOS (через Homebrew)
brew install sdl2 sdl2_ttf
```

## Сборка

```bash
mkdir build && cd build
cmake ..
make
```

## Запуск

С параметрами по умолчанию (500x300, скорость 5): 

```bash
./Game_of_Life
```
С пользовательскими параметрами
```bash
./Game_of_Life [ширина] [высота] [скорость]
# Пример:
./Game_of_Life 800 800 10
```