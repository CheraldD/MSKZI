import os
import datetime

# --- НАСТРОЙКИ ---
# Директория, в которой находится ваш проект. '.' означает 'текущая директория'.
PROJECT_DIR = '.' 
# Имя конечного Markdown-файла.
OUTPUT_FILE = 'project_code_summary.md'
# Расширения файлов, которые нужно включить в отчет.
FILE_EXTENSIONS = ('.h', '.cpp')
# Имена файлов без расширения, которые также нужно включить.
SPECIAL_FILES = ['Makefile']
# --- КОНЕЦ НАСТРОЕК ---

def create_code_summary():
    """
    Находит все исходные файлы в проекте и объединяет их в один Markdown-файл.
    """
    try:
        # Открываем (или создаем) выходной файл для записи.
        # encoding='utf-8' важен для корректной работы с кириллицей в комментариях.
        with open(OUTPUT_FILE, 'w', encoding='utf-8') as md_file:
            # Записываем общий заголовок документа.
            md_file.write(f'# Сводка по коду проекта\n\n')
            md_file.write(f'**Сгенерировано:** {datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")}\n\n')

            print("Начинаю сборку кода в Markdown-файл...")

            # Проходим по всем файлам и папкам в указанной директории.
            for root, dirs, files in os.walk(PROJECT_DIR):
                # Сортируем файлы, чтобы порядок был предсказуемым (например, .h перед .cpp)
                for filename in sorted(files):
                    
                    is_extension_match = filename.endswith(FILE_EXTENSIONS)
                    is_special_file = filename in SPECIAL_FILES

                    # Если файл подходит по расширению или имени...
                    if is_extension_match or is_special_file:
                        file_path = os.path.join(root, filename)
                        
                        # Пропускаем сам скрипт, если он находится в этой же папке.
                        if os.path.abspath(file_path) == os.path.abspath(__file__):
                            continue

                        print(f" -> Добавляю файл: {file_path}")

                        # 1. Записываем заголовок с именем файла.
                        md_file.write(f'## `{filename}`\n\n')

                        # 2. Определяем язык для подсветки синтаксиса.
                        lang = ''
                        if filename.endswith(('.h', '.cpp')):
                            lang = 'cpp'
                        elif filename == 'Makefile':
                            lang = 'makefile'

                        # 3. Открываем Markdown-блок для кода с указанием языка.
                        md_file.write(f'```{lang}\n')

                        # 4. Читаем содержимое исходного файла и записываем его в .md.
                        try:
                            with open(file_path, 'r', encoding='utf-8') as src_file:
                                md_file.write(src_file.read())
                        except Exception as e:
                            md_file.write(f"Не удалось прочитать файл. Ошибка: {e}")
                        
                        # 5. Закрываем Markdown-блок.
                        md_file.write('\n```\n\n')
        
        print(f"\n[УСПЕШНО] Вся работа завершена!")
        print(f"Результат сохранен в файле: {os.path.abspath(OUTPUT_FILE)}")

    except Exception as e:
        print(f"\n[ОШИБКА] Произошла ошибка во время выполнения скрипта: {e}")

if __name__ == "__main__":
    create_code_summary()