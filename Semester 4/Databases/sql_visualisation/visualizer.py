from graphviz import Digraph

# Create a new directed graph
dot = Digraph(comment='Database Schema')

# Add nodes for main tables
dot.node('W', 'WYDZIAŁ (NrW, Nazwa, Adres)')
dot.node('D', 'DZIECKO (NrAUr, Imie)')
dot.node('P', 'PRACOWNIK (NrP, Nazwisko, Stanowisko, Pensja)')
dot.node('PR', 'PROJEKT (IdP, Nazwa, Koszt)')

# Add nodes for associative tables
dot.node('Z', 'Zatrudnia (NrW, NrP, DataOd)')
dot.node('M', 'Ma (NrP, NrAUr, Zasilek)')
dot.node('WY', 'Wykonuje (NrP, IdP, DataOd, DataDo)')
dot.node('K', 'Kieruje (NrP, IdP, DataRozp)')

# Add edges to represent foreign key relationships
# Corrected edges to represent foreign key relationships
dot.edges([('W', 'Z'), ('P', 'Z'), ('P', 'M'), ('D', 'M'), ('P', 'WY'), ('PR', 'WY'), ('P', 'K'), ('PR', 'K')])


# Print the source code for the graph
print(dot.source)

# Render the graph to a file (PDF)
dot.render('/mnt/data/database_schema_diagram', format='pdf', view=True)
