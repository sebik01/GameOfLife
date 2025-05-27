Proiect game of life PA 2025.

Proiectul simuleaza jocul lui Conway si are si cateva taskuri in plus.

Task1:
Simuleaza jocul si se foloseste de doua matrici, o regula si un numar de generatii. Folosesc doua matrici pentru ca schimbarea sa fie uniforma, respectand cerinta ca fiecare celula
sa se supuna la aceleasi reguli fara schimbari variabile in timp.


Task2:
Pentru a stoca schimbarea dintre generatii intr-un mod eficient, am pastrat coordonatele celulelor care si-au schimbat starea (viu-->mort sau mort-->viu) intr-o lista inaltuita, 
necunoscand cate celule isi vor schimba starea.

Task3:
Am adaugat o noua regula, ca orice celula cu 2 vecini devine vie, si nu moare niciuna. Am pastrat intr-un arbore binar toate posibilitatile de a ajunge la o posibila pozitie pe 
tabla, ca un amestec dintre generatiile de la regula normala si cea noua. Un fel de codul morse.

Eu am abordat urmatoarea metoda, am facut o functie care imi genereaza arborele cunoscand matricea initiala, numarul de generatii si regulile. Pentru nodul urmator din stanga, se 
aplica regula noua, pentru un nod din dreapta, regula standard. Functia creaza blocuri pe heap si recursiv returneaza adresele 'next-urilor' unor noduri, respectiv NULL 
daca este depasita generatia. Pentru a face codul dintr-o bucata, am facut o parte care initializeaza si radacina, folosind o a 3-a regula.

Se primeste o matrice de start, si radacina tine minte intr-o lista coordonatele celulelor vii, iar urmatoarele noduri tin minte celulele care si-au modificat starea.
Pentru afisare, aplic acelasi algoritm, facand de asemenea deosebire intre generatia precedenta si curenta.


Task4:
Trebuie sa gasesc cea mai mare insula de celule vii care poate fi desenata in intregime fara a trece de 2 ori printr-o celula si a avea un desen continuu.
Eu am abordat asa, am creat un tip de data numit 'componenta_conexa' care tine minte toate celulele care comunica unul cu altul (sau altfel spus, care daca reprezinta un graf,
atunci graful rezultat este conex). De asemenea, pastrez si numarul de noduri, pentru a identifica un ciclu hamiltonian (iterez intr-o functie, si daca contorul meu este egal 
cu numarul de noduri, atunci ciclul / iteratia mea implica un drum Hamiltonian. Iterez prin fiecare componenta conexa si aleg drumul cel mai mare sau valid.

! daca sunt mai multe drumuri de aceeasi lungime, atunci eu trb sa aleg numai unul, si anume cel care incepe de pe cea mai mica linie / coloana in caz de tiebreak, urmand sa 
continue cu celule in care indicii de linie / coloana in caz de tiebreak sunt crescatori, dar in acelasi timp sa reprezinte un drum VALID.
