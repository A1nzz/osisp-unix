#!/bin/bash

# Отключить вывод курсора
tput civis

# Получить размеры терминала
cols=$(tput cols)
rows=$(tput lines)

# Функция для генерации случайной позиции
generate_random_position() {
  # Получить текущее время в секундах
  seed=$(date +%s)
  
  multiplier=1664525
  increment=1013904223
  modulus=$((2**32))

  seed=$((seed * multiplier + increment))
  seed=$((seed % modulus))
  # Константы для мультипликативного метода
  
  # Вычисление координат x и y
  x=$((seed % (cols - 12)))  # 12 - длина рамки и формата времени "HH:MM:SS"
  y=$((seed % (rows - 3)))   # 3 - высота рамки
}

# Функция для отрисовки текущего времени в рамке
draw_current_time() {
  tput cup $y $x

  # Отрисовка верхней границы рамки
  echo -n "+"
  for ((i=0; i<10; i++)); do
    echo -n "-"
  done
  echo "+"

  # Отрисовка времени в середине рамки
  tput cup $((y+1)) $((x+2))
  date +"%H:%M:%S"

  # Отрисовка нижней границы рамки
  tput cup $((y+2)) $x
  echo -n "+"
  for ((i=0; i<10; i++)); do
    echo -n "-"
  done
  echo "+"
}

# Основной цикл экранной заставки
while true; do
  # Очистить экран перед рисованием времени
  tput clear

  # Генерировать новую случайную позицию каждые 5 секунд
  if [ $((SECONDS % 5)) -eq 0 ]; then
    generate_random_position
  fi

  # Отрисовать текущее время в текущей позиции
  draw_current_time

  # Подождать 1 секунду
  sleep 1

done

# Включить вывод курсора после окончания
tput cnorm
