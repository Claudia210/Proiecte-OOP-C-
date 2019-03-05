# Proiecte-OOP-C++
Tema1-Coada-de-caractere
   Clasa ”Coada_de_caractere” (implementata dinamic)
Se considera Class Nod{ char info; Nod* next;}
- constructori de inițializare și parametrizati pentru clasa Nod;
- destructor pentru clasa Nod;
Clasa Coada_de_caractere are:
- membri privati, "Nod*, Nod*" (primul și ultimul element al cozii);
 - un constructor care initializeaza coada cu NULL;
 - un destructor care dezaloca toate elementele cozii;
- metode publice de adaugare a unui element în stiva (push), de stergere a unui
element (pop) și pentru a testa daca e vida (isempty);
- metoda publica de fisarea a cozii, concomitent cu golirea ei, realizata prin
supraincarcarea operatorului <<;
- supraincarcarea operatorului >>, realizata prin push-uri succesive;
- metoda publica pentru concatenarea a doua cozi de caractere, obtinand o alta coada
de caractere, implementata prin supraincarcarea operatorului +;
- metoda publica, realizata prin supraincarcarea operatorului -, care sa considere doua
cozi și sa elimine, concomitent, elementele din ambele cozi adaugand caracterul ce are
codul ASCII mai mare într-o noua coada, ca în exemplul de mai jos:
Coada_de_caractere C1,C2;
C1 = {E,X,A,M,E,N}; C2 = {P,O,O,L,A,B,O,R,A,T,O,R} C1 - C2 = {P,X,O,M,E,N}.

Tema2-Coada-cu-prioritati
  Cozi de caractere (implementate dinamic):
Se dau urmatoarele clase:
- Nod (char info, nod*next)
- Coada (nod * prim, nod * ultim, int dim_max);
- DEQUE : Coada - cu operatiile de adaugare și stergere modificate
corespunzator.
- CoadaPrioritati (int *prioritate) : Coada - cu operatiile de adaugare și
stergere modificate corespunzator.
Obs. Prioritate – vector alocat dinamic care conține prioritatea
pentru fiecare element .
Clasele derivate trebuie sa contina cel puțin constructori parametrizati (prin
care sa se evidentieze transmiterea parametrilor catre constructorul din clasa
de baza) si destructor. Simulați operatiile pe o stiva, respectiv pe o coada,
folosind coada cu prioritati. 

Tema3-Personal distributie film
