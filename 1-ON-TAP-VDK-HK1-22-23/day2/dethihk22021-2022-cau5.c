void ShowArray()
{
	unsinged int8 i,j,temp;
	lcd_gotoxy(1,1); //xuat array chua sap xep ra hang 1
	for(i=0;i<16;i++)
	{
		lcd_putc(A[i]+0x30);	
	}
	
	for(i=0;i<15;i++)
	{
		for(j=i+1;j<16;j++)
		{
			if(A[i]>A[j]) 
			{
				temp=A[j];
				A[j]=A[i];
				A[i]=temp;
				//A[i]=A[i]+A[j]  
				//A[j]=A[i]-A[j]				
				//A[i]=A[i]-A[j]	
			}				
		}
		
	}
	lcd_gotoxy(2,1);//xuat array da sap xep ra hang 2
	for(i=0;i<16;i++)
	{
		lcd_putc(A[i]+0x30);	
	}
}