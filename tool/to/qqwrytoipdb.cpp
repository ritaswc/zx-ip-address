#include <stdio.h>
#include <map>
#include <string>
#include "ipsearcher.h"
using namespace std;

#define offlen 3
#define iplen 4
#define OFFLEN 3

const char* weizhi="\xE6\x9C\xAA\xE7\x9F\xA5\xE5\x9C\xB0\xE5\x8C\xBA";
const string sweizhi=string(weizhi);
char *ipwrydata;

int read(){
	FILE *fp,*fp2;
	char *s1,*s2,*cp;
	IPV4 ip4,ip42;
	unsigned int thisip,nextip;
	__int64 line=-1, i, indexstart, indexcount, offset, off2;
	int flen;

	printf("opening file qqwry.dat...\n");

	fp2 = fopen("out-qqwry.txt","wt");

	fp = fopen("qqwry.dat","rb");
	fseek(fp, 0, 2);
	flen = ftell(fp);
	fseek(fp, 0, 0);
	ipwrydata = (char*)malloc(flen + 8);	// intn在文件末尾会越界
	memset(ipwrydata, 0, flen + 8);
	fread(ipwrydata, 1, flen, fp);
	fclose(fp);

	fprintf(fp2,"STARTIP\tENDIP\tCOUNTRY\tLOCAL\n");

	indexstart=*(int*)&ipwrydata[0];
	indexcount=(*(int*)&ipwrydata[4]-indexstart)/(iplen+offlen)+1;
	thisip=nextip=0;
 	for(i=0;i<=indexcount-1;i++){
		thisip=*(int*)&ipwrydata[indexstart+i*(iplen+offlen)];
		if(i==indexcount-1)
			nextip=0;
		else
			nextip=*(int*)&ipwrydata[indexstart+(i+1)*(iplen+offlen)];
		ip4=thisip;
		ip42=nextip-1;

		offset=intn(&ipwrydata[indexstart+i*(iplen+offlen)+iplen],offlen);
		offset+=4;
redir:
		switch(ipwrydata[offset]){
			case 1:
				offset=intn(&ipwrydata[offset+1],offlen);
				goto redir;
			case 2:
				off2=intn(&ipwrydata[offset+1],offlen);
				offset+=offlen+1;
				break;
			default:
				off2=offset;
				cp=strchr(&ipwrydata[off2],0);
				offset=cp-ipwrydata+1;
				break;
		}
		s1=&ipwrydata[off2];
		switch(ipwrydata[offset]){
			case 1:
			case 2:
				off2=intn(&ipwrydata[offset+1],offlen);
				break;
			default:
				off2=offset;
				break;
		}
		s2=&ipwrydata[off2];

		//fprintf(fp2,"%d.%d.%d.%d\t%d.%d.%d.%d\t%s\t%s\n",
		fprintf(fp2,"%03d.%03d.%03d.%03d\t%03d.%03d.%03d.%03d\t%s\t%s\n",
			ip4.n[3],ip4.n[2],ip4.n[1],ip4.n[0],
			ip42.n[3],ip42.n[2],ip42.n[1],ip42.n[0],
			s1,s2);

		//lastip=thisip;
	}
	
	fclose(fp2);

	free(ipwrydata);

	return 0;
}

int conv(){
	FILE *fp;
	wchar_t *newdata=NULL;
	unsigned int flen,newlen,tmp;

	printf("converting from ANSI to UTF8...\n");

	fp=fopen("out-qqwry.txt","rb");
	fseek(fp,0,2);
	flen=ftell(fp);
	fseek(fp,0,0);
	ipwrydata=(char*)malloc(flen+1);
	fread(ipwrydata,1,flen+1,fp);
	fclose(fp);
	ipwrydata[flen]=0;

	newlen=atow(0,ipwrydata,0);
	newdata=(wchar_t*)malloc(newlen*sizeof(wchar_t));
	tmp=atow(newdata,ipwrydata,newlen);
	free(ipwrydata);
	flen=wtoutf8(0,newdata,0);
	ipwrydata=(char*)malloc(flen);
	tmp=wtoutf8(ipwrydata,newdata,flen);
	fp=fopen("out-qqwry.txt","wb");
	fwrite(ipwrydata,1,flen-1,fp);
	fclose(fp);
	free(newdata);
	free(ipwrydata);

	return 0;
}

int write(){
	FILE *fp,*fp2;
	char ip1[100],ip2[100],s1[100],s2[200],s0[300],buf[300]={'I','P','D','B',1,0,OFFLEN,4,0},*token,
		outbuf[300];
	IPV4 ip4,ip42;
	map<string,unsigned int> m;
	map<string,unsigned int>::iterator mi;
	map<unsigned int,unsigned int> addm,mylist;
	map<unsigned int,unsigned int>::iterator addmi,mylisti;
	unsigned __int64 count=0,off,tmpoff,newoff,indexoff,tmp64,outbufoff,last64;
	int len0,len1,len2,tmp,zero=0,i;
	string str0,str1,str2;
	const char *f[]={
		"out-qqwry.txt",
	};

	fp2=fopen("qqwry.db","wb");
	fwrite(buf,32,1,fp2);

	off=40;
	fwrite(&off, 8, 1, fp2);
	fp=fopen("verqqwry.txt","r");
	fseek(fp,0,2);
	len0=ftell(fp);
	fseek(fp,0,0);
	fread(s0, 1, len0, fp);
	fclose(fp);
	s0[len0] = 0;
	fwrite(s0, 1, strlen(s0) + 1, fp2);
	off += strlen(s0) + 1;

	for(i=0;i<1;i++){
		fp=fopen(f[i],"rt");

		printf("converting txt file %s to db...\n", f[i]);

		fgets(buf,300,fp);
		while(fgets(buf,300,fp)!=NULL){
			token=strtok(buf,"\t");
			strcpy(ip1,token);
			token=strtok(NULL,"\t");
			strcpy(ip2,token);
			token=strtok(NULL,"\t");
			if(token==NULL){
				s1[0]=0;
			}else{
				strcpy(s1,token);
			}
			token=strtok(NULL,"\n");
			if(token==NULL){
				s2[0]=0;
			}else{
				strcpy(s2,token);
			}

			sprintf(s0,"%s\t%s",s1,s2);
			len1=strlen(s1);
			str1.assign(s1);
			len2=strlen(s2);
			str2.assign(s2);
			len0=strlen(s0);
			str0.assign(s0);

			alignip(&ip4,ip1);
			alignip(&ip42,ip2);
			outbufoff=0;

			mi=m.find(str0);
			if(mi==m.end()){
				m.insert(make_pair(str0,off));

				if(len1<OFFLEN){
					memcpy(outbuf+outbufoff,s1,len1+1);
					outbufoff+=len1+1;
				}else{
					mi=m.find(str1);
					if(mi==m.end()){
						m.insert(make_pair(str1,off+outbufoff));
						memcpy(outbuf+outbufoff,s1,len1+1);
						outbufoff+=len1+1;
					}else{
						outbuf[outbufoff]=2;
						tmpoff=(*mi).second;
						*(__int64*)&outbuf[outbufoff+1]=tmpoff;
						outbufoff+=OFFLEN+1;
					}
				}
				
				if(len2<OFFLEN){
					memcpy(outbuf+outbufoff,s2,len2+1);
					outbufoff+=len2+1;
				}else{
					mi=m.find(str2);
					if(mi==m.end()){
						m.insert(make_pair(str2,off+outbufoff));
						memcpy(outbuf+outbufoff,s2,len2+1);
						outbufoff+=len2+1;
					}else{
						outbuf[outbufoff]=2;
						tmpoff=(*mi).second;
						*(__int64*)&outbuf[outbufoff+1]=tmpoff;
						outbufoff+=OFFLEN+1;
					}
				}

				fwrite(outbuf,1,outbufoff,fp2);

				newoff=off;

			}else{
/*
				outbuf[outbufoff]=1;
				tmpoff=(*mi).second;
				*(__int64*)&outbuf[outbufoff+1]=tmpoff;
				outbufoff+=OFFLEN+1;
*/
				newoff=(*mi).second;
			}
			
			if(!mylist.empty()){
				mylisti=mylist.lower_bound(ip42.num);
				if(mylisti!=mylist.begin()){
					while( mylisti!=mylist.begin() ){
						mylisti--;
						if( (*mylisti).second < ip42.num ){
							if( (*mylisti).second < ip4.num ){
								mylist.insert(make_pair(ip4.num,ip42.num));
								addm.insert(make_pair(ip4.num,newoff));
							}else{
								mylist.insert(make_pair((*mylisti).second+1,ip42.num));
								addm.insert(make_pair((*mylisti).second+1,newoff));
							}
						}
						if( (*mylisti).first <= ip42.num )
							ip42.num=(*mylisti).first-1;

						if( ip42.num < ip4.num )
							break;
					}
				}else{
					addm.insert(make_pair(ip4.num,newoff));
					mylist.insert(make_pair(ip4.num,ip42.num));
				}
			}else{
//			if(addmi==addm.end()){
				addm.insert(make_pair(ip4.num,newoff));
				mylist.insert(make_pair(ip4.num,ip42.num));
//			}else{
//				if(strcmp(s2,weizhi)==0){
//					//count--;
//				}else{
//					(*addmi).second=newoff;
//				}
			}

/*			addmi=addm.find(ip6.num64());
			if(addmi==addm.end()){
				addm.insert(make_pair(ip6.num64(),newoff));
			}else{
				if(strcmp(s2,weizhi)==0){
					//count--;
				}else{
					(*addmi).second=newoff;
				}
			}
*/
			off+=outbufoff;
			
			count++;
			if(count%10000==0)printf("writing off %I64p , rec %I64d...\n", off, count);

		}

		fclose(fp);
	}

	printf("writing db...\n");

	indexoff=ftell(fp2);
	fseek(fp2,0x10,0);
	count=addm.size();
	fwrite(&indexoff,sizeof(__int64),1,fp2);
	fseek(fp2,indexoff,0);
	last64=0;
	for(addmi=addm.begin();addmi!=addm.end();addmi++){
		tmp64=(*addmi).second;
		if(tmp64==last64){
			count--;
			continue;
		}
		last64=tmp64;
		tmp64=(*addmi).first;
		fwrite(&tmp64,sizeof(int),1,fp2);
		fwrite(&last64,OFFLEN,1,fp2);
	}
	fseek(fp2,8,0);
	fwrite(&count,sizeof(__int64),1,fp2);
	fclose(fp2);
	


	return 0;
}

int main(){
	read();
	conv();
	write();
	return 0;
}

