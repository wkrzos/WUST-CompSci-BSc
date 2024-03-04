{
 "cells": [
  {
   "cell_type": "markdown",
   "metadata": {},
   "source": [
    "# Krótkie wprowadzenie do wybranych elementów języka Python oraz bibliotek obliczeń inżynierskich\n",
    "\n",
    "## Wstęp\n",
    "Ten plik jest de facto plikiem `html`. Możecie otworzy go w notatniku i zobaczycie zwykłą, statyczną stronę. To, że\n",
    "jego poszczególne sekcje możemy interpretowa jako kod, jest zasługą IPythona. Jupyter Notebook pozwala na \n",
    "**połączenie kodów źródłowych, ich opisów oraz wyników ich działania w jeden dokument**. Jest to jedno z najbardziej \n",
    "popularnych narzędzi w dziedzinie nauki o danych (ang. *data science*). Niemniej, polecam zapoznac się z przykładową\n",
    "[ściągą](https://www.edureka.co/blog/wp-content/uploads/2018/10/Jupyter_Notebook_CheatSheet_Edureka.pdf) ze skrótami \n",
    "klawiaturowymi.\n",
    "\n",
    "## Typy komórek\n",
    "Każda komórka notatnika stanowi osobny edytor z kodem, który może zostać wykonany na żądanie. Wszystkie komórki w \n",
    "obrębie notatnika współdzielą przestrzeń nazw i pamięć. Ma to swoje wady i zalety. Mamy dwa typy komórek: \n",
    "- z kodem\n",
    "- z tekstem\n",
    "\n",
    "### Komórki z tekstem\n",
    "Komórki z tekstem formatujemy według składni Markdown [tu szybka ściąga](https://enterprise.github.com/downloads/en/markdown-cheatsheet.pdf).\n",
    "Ta komórka jest właśnie typu tekstowego.\n",
    "\n",
    "### Komórki z kodem\n",
    "Kod interpretowany jest według wybranego kernela. Jupyter pod względem podpowiadania składni zachowuje się podobnie jak \n",
    "terminal, tj. aby uzyska podpowiedź musimy nacisną tabulator. Mamy także dwa specjalne znaki, które zmianiają sposób\n",
    "interpretowania linijki, w której są użyte, lub też całej komórki:\n",
    "\n",
    "#### Funkcje magiczne\n",
    "IPytnon, a zatem i bazujący na nim Jupyter Notebook posiada w swojej składni tzw. magiczne funkcje (nie mylic z \n",
    "magicznymi metodami języka Python, np. `self.__call__`). Aby z nich skorzystac musimy uży prefiksu `%` lub `%%`:\n",
    "- użycie `%` powoduje zinterpretowanie całej lini jako funkcji magicznej,\n",
    "- użycie `%%` powoduje zinterpretowanie całej komórki jako funkcji magicznej.\n",
    "  \n",
    "[Tutaj](https://ipython.readthedocs.io/en/stable/interactive/magics.html) mamy pełny wykaz funkcji magicznych. Dla Was\n",
    "nie są one najistotniejsze, jednakże czasami przydają się bardzo - np do pomiaru czasu obliczeń albo konfiguracji\n",
    "zachowania biblioteki `matplotlib`.\n",
    "\n",
    "#### Dostęp do shella\n",
    "W notebooku mamy także dostęp do shella. Uzyskujemy go dzięki użyciu prefiksa `!`.\n",
    "\n",
    "## Uwagi końcowe\n",
    "Zakłada się, że student potrafi już programować i pewne absolutne podstawy da radę wywieść z przedstawionych kodów.\n",
    "To nie jest samodzielny kurs języka Python, a jedynie przedstawienie elementów istotnych dla zajęć laboratoryjnych.\n",
    "\n",
    "Przy korzystaniu z notatnika nie należy obawiać się **eksperymentowania z kodem** we własnych komórkach. **Pamiętaj** \n",
    "korzystać z notatnika w sposób aktywny, tzn. uczysz się przez eksperymentowanie z zaproponowanym kodem. Nie licz \n",
    "wyłącznie na opisy, które z założenia są na ogół zdawkowe."
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": [
    "print(\"Hello world!\")  # wykonujemy zwyczajne polecenia Pythona\n",
    "\n",
    "%time  # wykonujemy funkcję magiczną\n",
    "\n",
    "!pwd"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "qaWgSgBKmyZJ"
   },
   "source": [
    "## Struktury danych języka Python, które omówione są w notatniku:\n",
    "* **lista**,\n",
    "* krotka,\n",
    "* **słownik**,\n",
    "* zbiór."
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "xtcD_N7onTEh"
   },
   "source": [
    "**Lista** <br>\n",
    "Jest to uporządkowana kolekcja obiektów dowolnego typu."
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "MXXYWH5njd_k",
    "outputId": "92d532e3-7b18-4756-9f45-d9d496cf1650"
   },
   "outputs": [],
   "source": [
    "miasta_lista = [\"Wrocław\", \"Opole\", \"Kraków\", \"Poznań\"]\n",
    "powierzchnia_lista = [292.8, 149, 147.9, 7.29]\n",
    "populacja_lista = [643782, 128140, 1200, 350]\n",
    "\n",
    "print(miasta_lista[1:3])"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "HwQRbs-jm1P4",
    "outputId": "b4f4a126-e255-4444-b808-7caf39fc8700"
   },
   "outputs": [],
   "source": [
    "miasta_lista.count(\"Wrocław\")"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "vYU9CqYHwPuV",
    "outputId": "345cbdc6-9e52-4047-d2bd-ec9fc77e2ae6"
   },
   "outputs": [],
   "source": [
    "\"Opole\" in miasta_lista"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "PWWc0OqTwRSd",
    "outputId": "4c914b5d-d890-41e9-a379-dcf42a06586f"
   },
   "outputs": [],
   "source": [
    "miasta_lista + miasta_lista"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "RE1pg-RczgOW"
   },
   "source": [
    "Iteracja po liście w stylu języka Java:"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "ILtEtSmFzkEQ",
    "outputId": "87d7569a-609f-44e3-a801-8ac59e441efc"
   },
   "outputs": [],
   "source": [
    "for i in range(len(miasta_lista)):\n",
    "    print(miasta_lista[i].upper())"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "XDaSQbNjz-q_"
   },
   "source": [
    "Iteracja po liście w stylu języka Python:"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "JKFPRroF1Xtt",
    "outputId": "cd1046a9-ab65-4bb8-d828-0f39325c04a6"
   },
   "outputs": [],
   "source": [
    "for elem in miasta_lista:\n",
    "    print(elem.upper())"
   ]
  },
  {
   "attachments": {},
   "cell_type": "markdown",
   "metadata": {
    "id": "IYwqmJmZ1fzw"
   },
   "source": [
    "Lista składana (ang. *list comprehension*) - jeden z elementów pythonicznego kodu."
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "9mJxSfqF1rUm",
    "outputId": "64944371-22a5-40c2-bc84-ae2ad3895ce7"
   },
   "outputs": [],
   "source": [
    "lista_skladana = [elem.upper() for elem in miasta_lista]\n",
    "print(lista_skladana)"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "eLEsi5642AFZ",
    "outputId": "2373af65-a102-4c00-ae7d-0c7f3f24a23f"
   },
   "outputs": [],
   "source": [
    "lista_skladana = [elem.upper() for elem in miasta_lista if elem.endswith(\"w\")]\n",
    "print(lista_skladana)"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "id": "fTtNztzcB1n0"
   },
   "outputs": [],
   "source": [
    "pusta_lista = []"
   ]
  },
  {
   "attachments": {},
   "cell_type": "markdown",
   "metadata": {},
   "source": [
    "Listy zagniezdzone - elementami danej listy są listy."
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": [
    "arr = [\n",
    "    [\"Wrocław\", \"Kłodzko\", \"Wałbrzych\"],\n",
    "    [\"Białystok\", \"Suwałki\", \"Augustów\"],\n",
    "    [\"Kraków\", \"Wieliczka\", \"Wadowice\"],\n",
    "]"
   ]
  },
  {
   "attachments": {},
   "cell_type": "markdown",
   "metadata": {},
   "source": [
    "**Ćwiczenie 1: Wypisz wszystkie miasta z tablicy `arr` korzystając z zagnieżdżonych pętli**"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": []
  },
  {
   "attachments": {},
   "cell_type": "markdown",
   "metadata": {},
   "source": [
    "Korzystając z funkcji `zip()` jesteśmy w stanie iterowac np. po dwóch tablicach na raz!"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": [
    "panstwa_lista = [\"Polska\", \"Czechy\", \"USA\", \"Korea Południowa\"]\n",
    "\n",
    "for m, p in zip(miasta_lista, panstwa_lista):\n",
    "    print(m, p)"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "TFLrEgs-x_Ps"
   },
   "source": [
    "Pamiętaj wykonać własne eksperymenty z listą. Zbadaj przy okazji, jakie są konsekwencje współdzielenia pamięci przez komórki notatnika."
   ]
  },
  {
   "attachments": {},
   "cell_type": "markdown",
   "metadata": {},
   "source": [
    "**Ćwiczenie 2: Sprawdź co się dzieje w przypadku iterowania przy uzyciu funkcji `zip()` po obiektach nierównej długości. Czy wiesz moze dlaczego?**"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": [
    "# Cwiczenie 2"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "a_EaNH7YzZ0W"
   },
   "source": [
    "**Krotka** <br>\n",
    "Można o niej mysleć jak o niemutowalnej (czyli niezmienialnej) liście."
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "id": "E6vH2T-iw5Dp"
   },
   "outputs": [],
   "source": [
    "wymiary = (90, 60, 90)"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/",
     "height": 174
    },
    "id": "PQkhJXVN2s57",
    "outputId": "e2ed57c3-e541-4c00-efcb-10547eb068cc"
   },
   "outputs": [],
   "source": [
    "wymiary[0] = 40"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "3uj2M8vY6Mio"
   },
   "source": [
    "Wprawdzie elementów składowych krotki nie da się zmienić, ale można zrobić to:"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "id": "rs85bek22v71"
   },
   "outputs": [],
   "source": [
    "wymiary = (1024, 768)"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "zJc1GVLg6bPk"
   },
   "source": [
    "**Zapamiętaj**: <br>\n",
    "\n",
    "1.   Python realizuje **dynamiczne typowanie**.\n",
    "2.   Nazwa w języku Python to pusty wskaźnik do obiektu (faktycznie implementowany jako ```void*``` w języku C). Jednak używając nazwy działasz na wskazywanym przez nią obiekcie. Zarządzaniem pamięcią zajmuje się Python.\n",
    "\n"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "jhOtUO8d7LlY"
   },
   "source": [
    "Tym co tworzy krotkę, jest nie tyle nawias ```()```, co przecinek:"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "id": "9Q2pK53O6aJg"
   },
   "outputs": [],
   "source": [
    "osoba = \"Bożydar\", 180, 92"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/",
     "height": 174
    },
    "id": "5rXcN-h-7l9J",
    "outputId": "af8d2fe1-f2a3-4265-bbfc-004c8a73f6ba"
   },
   "outputs": [],
   "source": [
    "osoba[2] = 88"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "id": "_9vTGBXq763D"
   },
   "outputs": [],
   "source": [
    "szer, wys = 1024, 768"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "blMp3PgiBnLF",
    "outputId": "19d11f82-f492-4c02-f686-717466caf742"
   },
   "outputs": [],
   "source": [
    "wys, szer = szer, wys\n",
    "print(f\"Szerokosć: {szer}\\nWysokość: {wys}\")"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "dc9kf_p7OSNw"
   },
   "source": [
    "Rozpakowanie krotki"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "I4tnKfe8OUhp",
    "outputId": "e8fe64d7-cd8a-4c33-f7fb-14d09b3452f2"
   },
   "outputs": [],
   "source": [
    "kolor = 122, 16, 196\n",
    "r, g, b = kolor\n",
    "print(f\"r = {r}, g = {g}, b = {b}\")"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "-jEtvZBaCBau"
   },
   "source": [
    "**Słownik**  (ang. *dictionary*) <br>\n",
    "Jest to nieuporządkowana kolekcja par <font color='blue'>*klucz*</font>-<font color='green'>*wartość*</font>."
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "id": "69CIgp98Bn8v"
   },
   "outputs": [],
   "source": [
    "populacja_dict = {\n",
    "    \"Wrocław\": 643782,\n",
    "    \"Opole\": 128140,\n",
    "    \"Złe Mięso\": 195,\n",
    "    \"Radom\": 210532,\n",
    "    \"Paryż\": 134,\n",
    "    \"Paryż\": 2148000,\n",
    "    \"Biłgoraj\": 27106,\n",
    "}\n",
    "\n",
    "powierzchnia_dict = {\n",
    "    \"Wrocław\": 292.8,\n",
    "    \"Opole\": 149,\n",
    "    \"Złe Mięso\": 4.38,\n",
    "    \"Radom\": 111.8,\n",
    "    \"Paryż\": 9.13,\n",
    "    \"Paryż\": 105.4,\n",
    "    \"Biłgoraj\": 21.1,\n",
    "}"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "Dj5clqvRL1JN",
    "outputId": "90f44f90-b6f9-41f1-aa4b-651e93b47d14"
   },
   "outputs": [],
   "source": [
    "populacja_dict[\"Paryż\"]"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "8_tr4WLDL2R5",
    "outputId": "8fde10ce-63f9-415e-da43-1aae2d187be9"
   },
   "outputs": [],
   "source": [
    "populacja_dict.keys()"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "QsJ92rN9N9h4",
    "outputId": "53f33960-aed5-4b4d-bc19-b47dfae5b562"
   },
   "outputs": [],
   "source": [
    "populacja_dict.values()"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "Lmki9Wb2ODJ1",
    "outputId": "a0e35d29-b100-482e-cbff-b6a6da388d46"
   },
   "outputs": [],
   "source": [
    "populacja_dict.items()"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "DooacriFOGoE"
   },
   "source": [
    "Iteracja po słowniku"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "wcvhVin9OE4o",
    "outputId": "d06864ce-4468-475e-c15c-28f6feb3487a"
   },
   "outputs": [],
   "source": [
    "for klucz, wartosc in populacja_dict.items():\n",
    "    print(f\"miasto: {klucz} | ludność: {wartosc}\")"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "bJEXGSVXOweC",
    "outputId": "0923ff28-375e-403e-a500-91648742b379"
   },
   "outputs": [],
   "source": [
    "\"Radom\" in populacja_dict"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "id": "cqBOJm5eB9DQ"
   },
   "outputs": [],
   "source": [
    "pusty_slownik = {}\n",
    "pusty_slownik = dict()"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "WIZhbLmyJpLL"
   },
   "source": [
    "**Zbiór** to coś na kształt słownika z samymi kluczami. <br>\n",
    "Możliwe, że przez cały kurs go nie użyjesz, ale warto znać. <br>\n",
    "Zamiast tłumaczenia przykład zastosowania."
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "TDl3E-vdJ_7n",
    "outputId": "d2e4ad4f-6373-4fda-ef91-19b19016ae51"
   },
   "outputs": [],
   "source": [
    "commiters_ordered = [\"Bolek\", \"ADU\", \"ADU\", \"Manny\", \"Bolek\", \"Manny\", \"Bolek\", \"ADU\"]\n",
    "commiters_unique = set(commiters_ordered)\n",
    "print(commiters_unique)"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "id": "7ltyIjiCLiTb"
   },
   "outputs": [],
   "source": [
    "pusty_zbior = set()"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "q6_LsIvEPUiz"
   },
   "source": [
    "## Biblioteczne struktury danych:\n",
    "* macierz ```numpy.ndarray```,\n",
    "* ramka danych  ```pandas.dataframe```,\n",
    "* seria danych ```pandas.series```."
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "ktKnWohxQG2G"
   },
   "source": [
    "**Macierz** (ang. *array*) <br>\n",
    "Jest to uporządkowana kolekcja obiektów tego samego typu (niekoniecznie liczby). <br>\n",
    "Biblioteka ```Numpy``` <br>\n",
    "Kluczowa dla obliczeń na macierzach."
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "id": "Fn54jxx_PIGd"
   },
   "outputs": [],
   "source": [
    "# jeśli nie działa\n",
    "!pip install numpy\n",
    "\n",
    "import numpy as np"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "id": "mgGIzKC8Qcbg"
   },
   "outputs": [],
   "source": [
    "tab = np.array([1, 1, 2, 3, 5, 8, 13])"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "NL7D3NRARbpd",
    "outputId": "fdf46dd7-daf6-4e28-8a36-ce6a653d91a6"
   },
   "outputs": [],
   "source": [
    "tab + tab"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "cMcIGLreRehN",
    "outputId": "44a69738-53ef-48bc-83a7-05e37892553d"
   },
   "outputs": [],
   "source": [
    "powierzchnia_tab = np.array(list(powierzchnia_dict.values()))\n",
    "print(list(powierzchnia_dict.values()))\n",
    "print(powierzchnia_tab)"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "N7rxFslNSifc",
    "outputId": "a86b8535-ef64-46e4-b0d5-c1e7fac6c549"
   },
   "outputs": [],
   "source": [
    "dane_ustandaryzowane = (powierzchnia_tab - powierzchnia_tab.mean()) / powierzchnia_tab.std()\n",
    "dane_ustandaryzowane = np.round(dane_ustandaryzowane, 2)\n",
    "print(dane_ustandaryzowane)"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "KZo0PXTATvUw",
    "outputId": "244d7edb-fe85-4229-fccb-1db553985b6d"
   },
   "outputs": [],
   "source": [
    "tab[-1]"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "yo_9kvixTRJj"
   },
   "source": [
    "Wycinki (ang. *slices*), czyli wybieranie z tabeli spójnych fragmentów."
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "r29ZDCuvSnr9",
    "outputId": "ef04bf2d-efe7-4f48-e76c-a30cb1deecd9"
   },
   "outputs": [],
   "source": [
    "tab = dane_ustandaryzowane.copy()\n",
    "print(tab)"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "DsFFqCqHTb9Q",
    "outputId": "29c1661c-c633-4ddd-b6c0-738eba4f8f5e"
   },
   "outputs": [],
   "source": [
    "tab[1:6:2]"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "OrelLndITuHN",
    "outputId": "3ecec52e-47de-44c1-fa25-723620f96655"
   },
   "outputs": [],
   "source": [
    "tab[:3]"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "DjRV2Hn4UJlY",
    "outputId": "dc691a36-e9a1-4173-a803-d1081b93dc6f"
   },
   "outputs": [],
   "source": [
    "tab[5:]"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "QlQk3EaYUK6K",
    "outputId": "c0c42b7a-2157-434f-aa49-6c614424063a"
   },
   "outputs": [],
   "source": [
    "tab[5:2:-1]"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "sXtv8ygBURk1",
    "outputId": "2b52c817-6f91-4bc1-e9f7-d05582ed4213"
   },
   "outputs": [],
   "source": [
    "tab[::-1]"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "Rl18qvcYV99z",
    "outputId": "f9fb368c-766a-415a-ef03-0e071fb7a471"
   },
   "outputs": [],
   "source": [
    "list(tab)"
   ]
  },
  {
   "attachments": {},
   "cell_type": "markdown",
   "metadata": {},
   "source": [
    "**Ćwiczenie 3: Opierając się na dokumentacji numpy zwiększ wartość każdego elementu `tab` o 3.14**"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": [
    "# Cwiczenie 3"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "z5xOMuDWx_vI"
   },
   "source": [
    "Filtrowanie, czyli wybieranie elementów spełniających określone kryteria."
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "j6lf8cZix_Ca",
    "outputId": "40c98fd5-caf6-48a0-bd41-1dc608af640e"
   },
   "outputs": [],
   "source": [
    "tab > 0"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "RQVkhxoZyFS-",
    "outputId": "e08bbf9d-1f66-4369-b510-c0485b32424b"
   },
   "outputs": [],
   "source": [
    "tab[tab > 0]"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "Kq7E2__sWHc3"
   },
   "source": [
    "**Seria** (ang. *series*) <br>\n",
    "Biblioteka ```Pandas``` <br>\n",
    "O serii można mysleć na dwa pożyteczne sposoby:\n",
    "\n",
    "*   jak o uporządkowanym słowniku,\n",
    "*   jak o tabeli, której indeks można dowolnie określać.\n",
    "\n"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "id": "fbgBxXhuWB84"
   },
   "outputs": [],
   "source": [
    "# jeśli nie działa\n",
    "!pip install pandas\n",
    "\n",
    "import pandas as pd"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "YqsitV9YdOsD",
    "outputId": "41ad712f-9d5e-44e5-d420-fb9995982dc9"
   },
   "outputs": [],
   "source": [
    "seria = pd.Series([1, 2, 3, 4], index=[\"a\", \"b\", \"c\", \"d\"])\n",
    "seria"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "e1UddwiQdQzm",
    "outputId": "c6069f71-57d9-4199-f3fc-739bacd801db"
   },
   "outputs": [],
   "source": [
    "seria[\"b\":\"d\"]"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "ciAv5Q9fdToC",
    "outputId": "24870680-e414-4bc0-cddb-b18684f254c4"
   },
   "outputs": [],
   "source": [
    "seria_ind = pd.Series([1, 2, 3, 4], index=[4, 3, 2, 1])\n",
    "seria_ind"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "qAQgHZh3dfFq"
   },
   "source": [
    "Jak w sposób jawny odwoływać się do indeksów zdefiniowanych lub domyślnych?"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "_5W7sz42da-2",
    "outputId": "6295129f-3d9f-4213-9c75-f874b4e08fc3"
   },
   "outputs": [],
   "source": [
    "print(seria_ind[3])\n",
    "print(seria_ind.loc[3])\n",
    "print(seria_ind.iloc[3])"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "n5pCKq5hdyPy"
   },
   "source": [
    "Konstruktor serii - jak pożytecznie indeksować."
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "I7LY1zHJdq7X",
    "outputId": "20769fa6-9f7a-48eb-8675-9241874e168a"
   },
   "outputs": [],
   "source": [
    "powierzchnia_series = pd.Series(powierzchnia_lista, index=miasta_lista)\n",
    "powierzchnia_series"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "_xL41VE6eQZn",
    "outputId": "89035a0a-c13d-4f4c-bda0-ff9631b09e41"
   },
   "outputs": [],
   "source": [
    "print(powierzchnia_series.index, powierzchnia_series.values, sep=\"\\n\")"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "id": "AzIsOkRuCTLs"
   },
   "outputs": [],
   "source": [
    "pusta_seria = pd.Series(dtype=\"int\")"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "yKuePSTaeslt"
   },
   "source": [
    "## Ramka danych (ang. *Data Frame*)\n",
    "Biblioteka ```Pandas``` <br>\n",
    "Ramka danych to kolekcja serii współdzielących indeks. <br>\n",
    "Przy wyświetlaniu zawartości ramki poleceniem ```display``` poszczególne serie znajdują się w kolumnach o odpowiednich nazwach. <br>\n",
    "Ramka danych jest najważniejszą strukturą z punktu widzenia nauki o danych. "
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/",
     "height": 331
    },
    "id": "ZsIcg_CveT4T",
    "outputId": "5cbad258-8b2b-4c43-9b08-8368fd2f6f1c"
   },
   "outputs": [],
   "source": [
    "df = pd.DataFrame({\"populacja\": populacja_dict, \"powierzchnia\": powierzchnia_dict})\n",
    "display(df)"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/"
    },
    "id": "wJWVmI1HfRlW",
    "outputId": "76aff9aa-84e0-4203-d2d8-cecece6790fd"
   },
   "outputs": [],
   "source": [
    "print(df.index, df.columns, sep=\"\\n\")"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "id": "AneCTk65fUmw"
   },
   "outputs": [],
   "source": [
    "df.loc[\"Radom\", \"powierzchnia\"] = 112"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/",
     "height": 331
    },
    "id": "8Ln3f9lBfX3j",
    "outputId": "d34a24b5-0eca-4aaa-8c36-0d2174c10778"
   },
   "outputs": [],
   "source": [
    "df[[\"populacja\"]]"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "fLNIqRYEfeIY"
   },
   "source": [
    "Transpozycja ramki"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/",
     "height": 112
    },
    "id": "7qK9rHn2fiv8",
    "outputId": "1710fc95-e98b-40e6-afed-b660a8a63eb3"
   },
   "outputs": [],
   "source": [
    "df.T"
   ]
  },
  {
   "attachments": {},
   "cell_type": "markdown",
   "metadata": {
    "id": "sjILqrA_NuGQ"
   },
   "source": [
    "**Cwiczenie 4:** Zbadaj jaka jest różnica między `df.T[['Wrocław']]`, a `df.T['Wrocław']`.\n",
    "Jakiego typu są obydwa obiekty?"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": [
    "# Cwiczenie 4"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/",
     "height": 331
    },
    "id": "slL-Mwb3fc7H",
    "outputId": "b62d7148-8431-4705-e35c-0250b1d9a843"
   },
   "outputs": [],
   "source": [
    "df.rename(columns={\"populacja\": \"pop\", \"powierzchnia\": \"pow\"})"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/",
     "height": 331
    },
    "id": "lRCDmNLdxx99",
    "outputId": "1f272061-819e-4fb0-cbee-db7f93721899"
   },
   "outputs": [],
   "source": [
    "df.replace(48, \"zadziurze\")"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/",
     "height": 331
    },
    "id": "VYxwPXBjx2ew",
    "outputId": "538c364d-c821-49d3-e26d-e8b3c389af59"
   },
   "outputs": [],
   "source": [
    "df.rename(index={\"Wrocław\": \"W-w\"})"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "id": "g6OTZwfdCvCA"
   },
   "outputs": [],
   "source": [
    "pusta_ramka = pd.DataFrame(dtype=\"float64\")"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "xX-7_OMbyofL"
   },
   "source": [
    "### Rysowanie prostych wykresów\n",
    "Biblioteka ```Matplotlib```"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "id": "PDL-Xowjx5T2"
   },
   "outputs": [],
   "source": [
    "# jeśli nie działa\n",
    "!pip install matplotlib\n",
    "\n",
    "import matplotlib.pyplot as plt"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "CfWRx4E4FZSd"
   },
   "source": [
    "Na początek prosty wykres bez typowych ozdobników."
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/",
     "height": 265
    },
    "id": "__hLM5Z5Ff5o",
    "outputId": "5d00be95-45c8-4b2a-cf3b-e3cb0e896903"
   },
   "outputs": [],
   "source": [
    "x = np.linspace(start=-2, stop=2, num=100)\n",
    "y = x**2\n",
    "plt.plot(x, y)"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "EHEtjAY3F92S"
   },
   "source": [
    "A teraz z ozdobnikami, których obecność jest bardzo wskazana w sprawozdaniach, publikacjach, pracach dyplomowych itp."
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/",
     "height": 297
    },
    "id": "pH13kdpby2V4",
    "outputId": "ee3354d3-87ba-43ca-9961-7a15dda5c51a"
   },
   "outputs": [],
   "source": [
    "fig, ax = plt.subplots(nrows=1, ncols=2, figsize=(10, 4))\n",
    "\n",
    "x = np.arange(start=0, stop=2, step=0.1)\n",
    "y = x**2\n",
    "ax[0].plot(x, y, marker=\".\")\n",
    "ax[0].set_xlabel(\"x\", fontsize=14)\n",
    "ax[0].set_ylabel(\"y\", fontsize=14)\n",
    "\n",
    "x = np.linspace(start=0, stop=6, num=100)\n",
    "y = np.sin(x) + np.sin(3 * x)\n",
    "ax[1].plot(x, np.sin(x), label=\"składnik 1\", alpha=0.8, linestyle=\"dashed\")\n",
    "ax[1].plot(x, np.sin(3 * x), label=\"składnik 2\", alpha=0.8, linestyle=\"dotted\")\n",
    "ax[1].plot(x, y, label=\"suma\", linewidth=3)\n",
    "ax[1].set_xlabel(\"x\", fontsize=14)\n",
    "ax[1].set_ylabel(\"y\", fontsize=14)\n",
    "ax[1].legend()\n",
    "fig.tight_layout()\n",
    "plt.show()"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {
    "id": "HzxGHik52Kjr"
   },
   "source": [
    "Laboratorium fal"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/",
     "height": 297
    },
    "id": "ptwyBm1UzL-o",
    "outputId": "8534225e-a8a8-434b-b55d-093b3f5311a3"
   },
   "outputs": [],
   "source": [
    "t = np.linspace(0, 2 * np.pi, 600)\n",
    "x = np.sin(3 * t)\n",
    "y = np.cos(5 * t)\n",
    "\n",
    "fig, ax = plt.subplots(nrows=1, ncols=2, figsize=(11, 4))\n",
    "\n",
    "ax[0].plot(t, x, label=\"x\")\n",
    "ax[0].plot(t, y, label=\"y\")\n",
    "ax[0].set_xlabel(\"t\", fontsize=14)\n",
    "ax[0].set_ylabel(\"wartość\", fontsize=14)\n",
    "ax[0].legend(fontsize=12)\n",
    "ax[0].set_title(\"wykres na osi czasu\")\n",
    "\n",
    "ax[1].plot(x, y)\n",
    "ax[1].set_xlabel(\"x\", fontsize=14)\n",
    "ax[1].set_ylabel(\"y\", fontsize=14)\n",
    "ax[1].axis(\"square\")\n",
    "ax[1].set_title(\"przestrzeń zmiennych stanu\")\n",
    "\n",
    "fig.tight_layout()\n",
    "plt.show()"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "colab": {
     "base_uri": "https://localhost:8080/",
     "height": 265
    },
    "id": "iUNqSQbd3Co6",
    "outputId": "38b02ad9-d700-4012-a620-90ab409bd3d2"
   },
   "outputs": [],
   "source": [
    "x = np.linspace(0, 20, 1001)\n",
    "y = np.zeros_like(x)\n",
    "\n",
    "N = 12100\n",
    "for i in range(1, N + 1, 2):\n",
    "    y += np.sin(i * x) / i\n",
    "\n",
    "plt.plot(x, y)\n",
    "plt.show()"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": []
  }
 ],
 "metadata": {
  "colab": {
   "collapsed_sections": [],
   "name": "MSiD_1_podstawowe narzędzia.ipynb",
   "provenance": []
  },
  "kernelspec": {
   "display_name": "Python 3",
   "name": "python3"
  },
  "language_info": {
   "codemirror_mode": {
    "name": "ipython",
    "version": 3
   },
   "file_extension": ".py",
   "mimetype": "text/x-python",
   "name": "python",
   "nbconvert_exporter": "python",
   "pygments_lexer": "ipython3",
   "version": "3.8.13"
  }
 },
 "nbformat": 4,
 "nbformat_minor": 0
}