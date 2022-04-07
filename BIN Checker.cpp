#include<bits/stdc++.h>
#include<Windows.h>
#include<conio.h>

std::string GetStdoutFromCommand(std::string cmd)
{
	std::string data;
	FILE* stream;
	const int max_buffer = 256;
	char buffer[max_buffer];
	cmd.append(" 2>&1");

	stream = _popen(cmd.c_str(), "r");
	if (stream) {
		while (!feof(stream))
			if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
		_pclose(stream);
	}
	return data;
}

std::string MaskToJson(std::string cmd_data)
{
	int x = -1;
	for (int i = 0; i < cmd_data.length(); i++)
	{
		x++;
		if (cmd_data[i] == '{')
			break;
	}
	cmd_data.erase(0, x);
	return cmd_data;
}

std::string GET_SCHEME(std::string x)
{
	x.erase(0, x.find("\"scheme\":\""));x.erase(0, 10);x.erase(x.find("\""),x.length());
	return x;
}

std::string GET_TYPE(std::string x)
{
	x.erase(0, x.find("\"type\":\"")); x.erase(0, 8); x.erase(x.find("\""), x.length());
	return x;
}

std::string GET_COUNTRY(std::string x)
{
	x.erase(0, x.find("\"name\":\"")); x.erase(0, 8); x.erase(x.find("\""), x.length());
	return x;
}

std::string GET_ISSUER(std::string x)
{
	x.erase(0, x.find("\":{\"name\":")); x.erase(0, 11); x.erase(x.find("\""), x.length());
	return x;
}
int main()
{
	
	std::cout<<"Enter the initial 6 digits(BIN) of your card : ";
	std::cout<<"Made with ❤ by Abin";
	
	std::string Bin;
	std::cin>>Bin;
	std::cout<<std::endl;
	std::string MainCMD = "curl -H \"Accept-Version: 3\" https://lookup.binlist.net/", FinSTR = MainCMD + Bin;
	
	std::string StdOut = MaskToJson(GetStdoutFromCommand(FinSTR));
	
	if(StdOut.length()>1){
		std::cout << std::endl << "1) SCHEME  : " + GET_SCHEME(StdOut);
		std::cout << std::endl << "2) TYPE    : " + GET_TYPE(StdOut);
		std::cout << std::endl << "3) COUNTRY : " + GET_COUNTRY(StdOut);
		std::cout << std::endl << "4) ISSUER : " + GET_ISSUER(StdOut);
	}
	else{
		std::cout<<"Wrong Card Details"<<std::endl;
	}

	
	getch();
	return 0;
}
