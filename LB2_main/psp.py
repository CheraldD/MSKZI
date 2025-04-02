import matplotlib.pyplot as plt
import re

# Функция для парсинга частот последовательностей
def parse_sequence_frequencies(data, sequence_length):
    pattern = re.compile(r'f(\d+):\s*(\d+)')
    frequencies = {}

    for match in re.finditer(pattern, data):
        seq = match.group(1)
        freq = int(match.group(2))

        # Составляем ключ с длиной последовательности
        if len(seq) == sequence_length:
            frequencies[seq] = freq
    return frequencies

# Функция для парсинга относительных частот
def parse_relative_frequencies(data, sequence_length):
    pattern = re.compile(r'(\d+):\s*([\d.]+)')
    frequencies = {}

    for match in re.finditer(pattern, data):
        seq = match.group(1)
        freq = float(match.group(2))

        # Составляем ключ с длиной последовательности
        if len(seq) == sequence_length:
            frequencies[seq] = freq
    return frequencies

# Функция для парсинга АКФ
def parse_acf(data):
    pattern = re.compile(r'(\d+):\s*([\d.-]+)')
    acf = []

    for match in re.finditer(pattern, data):
        acf.append(float(match.group(2)))

    return acf

# Функция для построения графиков
def plot_data(frequencies, label, title, xlabel, ylabel):
    sequences = list(frequencies.keys())
    values = list(frequencies.values())

    plt.figure(figsize=(10, 6))
    plt.bar(sequences, values)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.title(f"{title}: {label}")
    plt.xticks(rotation=90)
    plt.show()

# Основной процесс
def main(file_path):
    with open(file_path, 'r') as file:
        data = file.read()

    # Парсинг данных для различных последовательностей
    p1_frequencies = parse_sequence_frequencies(data, 1)
    p2_frequencies = parse_sequence_frequencies(data, 2)
    p3_frequencies = parse_sequence_frequencies(data, 3)
    p4_frequencies = parse_sequence_frequencies(data, 4)

    # Парсинг относительных частот
    p1_rel_freq = parse_relative_frequencies(data, 1)
    p2_rel_freq = parse_relative_frequencies(data, 2)
    p3_rel_freq = parse_relative_frequencies(data, 3)
    p4_rel_freq = parse_relative_frequencies(data, 4)

    # Парсинг АКФ
    acf_values = parse_acf(data)

    # Построение графиков
    plot_data(p1_frequencies, 'p1', 'Частоты появления последовательностей', 'Последовательность', 'Частота')
    plot_data(p2_frequencies, 'p2', 'Частоты появления последовательностей', 'Последовательность', 'Частота')
    plot_data(p3_frequencies, 'p3', 'Частоты появления последовательностей', 'Последовательность', 'Частота')
    plot_data(p4_frequencies, 'p4', 'Частоты появления последовательностей', 'Последовательность', 'Частота')

    plot_data(p1_rel_freq, 'p1', 'Относительные частоты последовательностей', 'Последовательность', 'Относительная частота')
    plot_data(p2_rel_freq, 'p2', 'Относительные частоты последовательностей', 'Последовательность', 'Относительная частота')
    plot_data(p3_rel_freq, 'p3', 'Относительные частоты последовательностей', 'Последовательность', 'Относительная частота')
    plot_data(p4_rel_freq, 'p4', 'Относительные частоты последовательностей', 'Последовательность', 'Относительная частота')

    plt.figure(figsize=(10, 6))
    plt.plot(range(len(acf_values)), acf_values, marker='o')
    plt.xlabel('Лаг')
    plt.ylabel('АКФ')
    plt.title('Автокорреляционная функция')
    plt.grid(True)
    plt.show()

# Запуск программы
if __name__ == '__main__':
    file_path = 'file_chars.txt'  # Замените на путь к вашему файлу
    main(file_path)
