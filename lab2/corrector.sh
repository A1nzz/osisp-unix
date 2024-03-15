#!/bin/bash

# Чтение содержимого файла в переменную
input_file="input.txt"
text=$(cat "$input_file")

# Разделение текста на предложения
sentences=$(echo "$text" | sed 's/[.!?]/&\n/g')

# Перебор каждого предложения и коррекция заглавных букв
corrected_text=""
previous_sentence_ended=1
digit=1

for sentence in $sentences; do\

    if [[ "$sentence" =~ ^[0-9].* ]]; then
        digit=1
    else
        digit=0
    fi
    if [ $previous_sentence_ended -eq 1 ]; then
        # Коррекция заглавной буквы в начале предложения
        corrected_sentence=$(echo "$sentence" | sed 's/^\([а-яa-z]\)/\U\1/')
        if [ $digit -eq 1 ]; then
        	corrected_text+="$corrected_sentence"
       	else
        	corrected_text+=" $corrected_sentence"   
        fi

    else
        corrected_text+=" $sentence"
    fi
    
    # Проверка, завершилось ли предложение точкой, не находящейся внутри числа
    if [[ "$sentence" =~ ^.*[.!?][[:space:]]*$ ]]; then
        previous_sentence_ended=1
    else
    	previous_sentence_ended=0
    fi
   
    
done

# Вывод скорректированного текста
echo "$corrected_text" > output.txt

