int main()
{
	char **ptr = ft_split("text", 'seaprteur');
	int i = 0;

	while(ptr[i])
	{
		puts(ptr[i]);
		i++;
	}
}