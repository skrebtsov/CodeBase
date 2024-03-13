#!/bin/bash
# Вывод сообщения об использовании каталога
if [ -z $1 ];then
echo "Usage :$(basename $0) parent-directory"
exit 1
fi

# Обработка всех подкаталогов и файлов в родительском каталоге
all="$(find $1 -depth)"

for name in ${all}; do
#Установка нового имени в нижнем регистре для файлов и каталогов
new_name="$(dirname "${name}")/$(basename "${name}" | tr '[A-Z]' '[a-z]')"

# Проверка, существует ли уже новое имя
if [ "${name}" != "${new_name}" ]; then
[ ! -e "${new_name}" ] && mv -T "${name}" "${new_name}"; echo "${name} was renamed to ${new_name}" || echo "${name} wasn't renamed!"
fi
done

echo
echo
# Вывод списка каталогов и файлов с новыми именами в нижнем регистре
echo "Directories and files with new names in lowercase letters"
find $(echo $1 | tr 'A-Z' 'a-z') -depth

exit 0
