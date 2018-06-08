node *quicksort(node *head)
{
	if (head->next == NULL)
	{
		return head;
	}
	if (head->next->next == NULL)
	{
		if (head->value > head->next->value) swap(head, head, head->next);
		return head->next;
	}
	node *low = NULL, *mid = NULL, *top = NULL;				//dzielimy na 3 listy-mniejsze, równe, większe
	float pivot = head->value;								//ustawiamy pivot na pierwszy element
	node *temp = head;
	node *last = NULL;
	node *lastMid = NULL;
	while (temp)  //przechodzimy całą nieposortowaną listę
	{
		node *next = temp->next;
		unlink(temp);
		if (temp->value < pivot) qsadd(low, temp); //dodajemy do mniejszych
		if (temp->value == pivot)	//dodajemy do równych
		{
			qsadd(mid, temp);
			if (!mid || mid && !mid->next) lastMid = temp;	//jeżeli element dodawany jest pierwszy bądź drugi, ustawiamy wskaźnik lastMid na ten element
			if (!top && !mid->next) last = temp; // jeżeli top nie istnieje i nie istnieje mid->next ustawiamy wskaźnik końca całości na temp
		}
		if (temp->value > pivot)	//dodajemy do większych
		{
			qsadd(top, temp);
			if (!top || (top && !top->next)) last = temp;	//jeżeli nie istnieje top lub nie istnieje top->next, ustawiamy last na dodawany element
		}
		temp = next;
	}
	node *lastLow = NULL;
	if (low)	//jeżeli istnieją elementy mniejsze, łączymy low z mid
	{
		lastLow = quicksort(low);//lastLow ustawiamy na ostatni element posortowanej już listy low; qs zwraca element ostatni
		lastLow->next = mid;	//łączenie
		mid->prev = lastLow;
	}
				//mid zawsze istnieje
	if (top)	//jeżeli istnieją elementy większe, łączymy mid z top
	{
		last = quicksort(top);	//last ustawiamy na ostatni element posortowanej listy top
		while (top->prev) top = top->prev;	//przesuwamy wskaźnik top na pierwszy element tej listy
		lastMid->next = top;		//łączenie
		top->prev = lastMid;
	}
	return last;
}
void quicksort(node *&head)
{
	head = quicksort(head);		//ustawiamy head na ostatni element posortowanej listy; nie jest konieczne, można pominąć przypisanie
								//wtedy head będzie gdzieś w środku posortowanej listy
	while (head->prev)	head = head->prev;	//przesuwamy head na początek
	return;
}
