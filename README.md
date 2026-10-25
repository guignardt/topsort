# topsort

Ein Programm, der eine topologische Ordnung eines eingegebenes Graphen bestimmt.

## Building

`topsort` kann mit [Make](https://www.gnu.org/software/make/) kompiliert werden.
Das Executable befindet sich dann in `build/topsort`.

## Nutzung

`topsort` nimmt als einziges Argument einen Pfad zu der Graphdatei ein. In der
ersten Zeile dieser sollte die Anzahl der Knoten stehen. In den nächsten Zeilen
sollten jeweils zwei Zahlen `x` und `y` stehen, die eine Kante von (`x`, `y`)
beschreiben.
