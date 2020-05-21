
void computeprefixfunction(const string &s){
	int i,border=0;
	for(i=1;i<s.length();i++){
		while(border>0 && s[i]!=s[border])
			border=pref[border-1];
		if(s[i]==s[border])
			border++;
		else
			border=0;
		pref[i]=border;
	}

}
