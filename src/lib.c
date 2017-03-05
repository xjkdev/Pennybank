// this file is to add algorithm for search and sort and filter
#include <stdio.h>
#include <stdlib.h>
#include <lib.h>
#include <list.h>
#include <stData.h>
int  cBalance(List *list,long index){
	Listnode *node;
	node=listIndexAt(list,index);
	Decimal n;
	n=node->value->amount;
	node=node->next;
	while(node!=NULL){
		node->value->balance-=n;
		node=node->next;
	}
	return 0;  
}
