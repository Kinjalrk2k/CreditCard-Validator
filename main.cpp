//  using Luhn algorithm

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <ctime>
#include <iomanip>
#include "menu_creator.cpp"

using namespace std;

struct spacing
{
    int f, s, t, fo, fi;
};


int calc_checksum_even(char card_no[])
{
    int checksum=0;
    for(int i=0; i<strlen(card_no); i++)
    {
        if(i%2 == 0)
        {
            int temp, dig;
            temp = (((int)card_no[i]-48)*2);

            if(temp>9)
            {
                dig=temp%10;
                temp/=10;
                dig+=temp;

                temp=dig;
            }

            checksum+=temp;
        }

        else
            checksum+=((int)card_no[i]-48);
    }

    return checksum;
}

int calc_checksum_odd(char card_no[])
{
    int checksum=0;
    for(int i=0; i<strlen(card_no); i++)
    {
        if((i+1)%2 == 0)
        {
            int temp, dig;
            temp = (((int)card_no[i]-48)*2);

            if(temp>9)
            {
                dig=temp%10;
                temp/=10;
                dig+=temp;

                temp=dig;
            }

            checksum+=temp;
        }

        else
            checksum+=((int)card_no[i]-48);
    }

    return checksum;
}

const char* get_industry(char card_no[])
{
    int MII;

    MII=((int)card_no[0]-48);

    switch(MII)
    {
    case 0:
        return "ISO/TC 68 and other industry assignments";
    case 1:
        return "Airlines";
    case 2:
        return "Airlines and other industry assignments";
    case 3:
        return "Travel & Entertainment";
    case 4:
        return "Banking & Financial";
    case 5:
        return "Banking & Financial";
    case 6:
        return "Merchandising & Finance";
    case 7:
        return "Petroleum";
    case 8:
        return "Telecommunications and other industry assignments";
    case 9:
        return "National Assignment";
    }
}


const char* get_issu_auth(char card_no[])
{
    int IIN=0;

    int exp = 5;
    for(int i=0; i<6; i++, exp--)
        IIN+=(((int)card_no[i]-48)*(pow(10,exp)));

    if(IIN/100000==4)
        return "Visa";

    if(IIN/100000==1)
        return "UATP";

    if(IIN/10000==34 || IIN/10000==37)
        return "American Express";

    if(IIN/10000==62)
        return "China UnionPay";

    if(IIN/10000==36 || (IIN/1000>=300 && IIN/1000<=305) || IIN/100==3095 || (IIN/10000>=38 && IIN/10000<=39))
        return "Diners Club International";

    if(IIN/10000==54 || IIN/10000==55)
        return "Diners Club United States & Canada (MasterCard co-branded)";

    if(IIN/10000==60 || IIN/100==6521)
        return "RuPay";

    if(IIN/10000==50 || (IIN/10000>=56 && IIN/10000<=58) || IIN/100000==6)
        return "Maestro";

    if(IIN/10000>=51 && IIN/10000<=55)
        return "MasterCard";

    if(IIN/1000==636)
        return "InterPayment";

    if(IIN/1000>=637 || (IIN/1000)<=639)
        return "InstaPayment";

    if(IIN/100==6011 || IIN/10000==64 || IIN/10000==65)
        return "Discover Card";

    if(IIN/100==5610 || (IIN>=560221 && IIN<=560225))
        return "Bankcard";

    if(IIN/100==2014 || IIN/100==2149)
        return "Diners Club enRoute";

    if(IIN/100>=3528 || IIN/100<=3589)
        return "JCB";

    if(IIN/100==6304 || IIN/100==6706 || IIN/100==6771 || IIN/100==6709)
        return "Laser";

    if(IIN/100==5019)
        return "Dankort";

    if(IIN/100==4571)
        return "Dankort (Visa co-branded)";

    if(IIN/100>=2200 && IIN/100<=2204)
        return "MIR";

    if(IIN/100>=2221 && IIN/100<=2720)
        return "MasterCard";

    if(IIN/100==6334 || IIN/100==6767)
        return "Solo";

    if(IIN/100==4903 || IIN/100==4905 || IIN/100==4911 || IIN/100==4936 || IIN/100==564182 || IIN/100==633110 || IIN/100==6333 || IIN/100==6759)
        return "Switch";

    if(IIN>=979200 && IIN<=979289)
        return "Troy";

    if((IIN>=506099 && IIN<=506198) || (IIN>=650002 && IIN<=650027))
        return "Verve";
}

spacing get_space(char card_no[], const char issu_auth[])
{
    if(strlen(card_no)==16)
    {
        spacing s;
        s.f=4;
        s.s=4;
        s.t=4;
        s.fo=4;
        s.fi=0;

        return s;
    }

    else
    {
        if(strcmp(issu_auth,"American Express") && strlen(card_no)==15)
        {
            spacing s;
            s.f=4;
            s.s=6;
            s.t=5;
            s.fo=0;
            s.fi=0;

            return s;
        }

        else if(strcmp(issu_auth,"Maestro"))
        {
            if(strlen(card_no)==13)
            {
                spacing s;
                s.f=4;
                s.s=4;
                s.t=5;
                s.fo=0;
                s.fi=0;

                return s;
            }

            else if(strlen(card_no)==15)
            {
                spacing s;
                s.f=4;
                s.s=6;
                s.t=5;
                s.fo=0;
                s.fi=0;

                return s;
            }

            else if(strlen(card_no)==19)
            {
                spacing s;
                s.f=4;
                s.s=4;
                s.t=4;
                s.fo=4;
                s.fi=3;

                return s;
            }
        }

        else if(strcmp(issu_auth,"Diners Club International") && strlen(card_no)==14)
        {
            spacing s;
            s.f=4;
            s.s=6;
            s.t=4;
            s.fo=0;
            s.fi=0;

            return s;
        }

        else if(strcmp(issu_auth,"UATP") && strlen(card_no)==15)
        {
            spacing s;
            s.f=4;
            s.s=5;
            s.t=6;
            s.fo=0;
            s.fi=0;

            return s;
        }

        else if(strcmp(issu_auth,"Diners Club enRoute") && strlen(card_no)==15)
        {
            spacing s;
            s.f=4;
            s.s=7;
            s.t=4;
            s.fo=0;
            s.fi=0;

            return s;
        }

        else if(strcmp(issu_auth,"Solo") && strlen(card_no)==19)
        {
            spacing s;
            s.f=4;
            s.s=4;
            s.t=4;
            s.fo=4;
            s.fi=3;

            return s;
        }

        else if(strcmp(issu_auth,"China UnionPay") && strlen(card_no)==19)
        {
            spacing s;
            s.f=6;
            s.s=13;
            s.t=0;
            s.fo=0;
            s.fi=0;

            return s;
        }


        else
        {
            spacing s;
            s.f=strlen(card_no);
            s.s=0;
            s.t=0;
            s.fo=0;
            s.fi=0;

            return s;
        }

    }
}

void print_card_no(char card_no[], const char issu_auth[])
{
    spacing s;

    s=get_space(card_no, issu_auth);

    int i=0;

    for(int j=0; j<s.f; j++, i++)
        cout<<card_no[i];
    cout<<" ";

    for(int j=0; j<s.s; j++, i++)
        cout<<card_no[i];
    cout<<" ";

    for(int j=0; j<s.t; j++, i++)
        cout<<card_no[i];
    cout<<" ";

    for(int j=0; j<s.fo; j++, i++)
        cout<<card_no[i];
    cout<<" ";

    for(int j=0; j<s.fi; j++, i++)
        cout<<card_no[i];

    if(s.s==0 && s.t==0 && s.fo==0 && s.fi==0)
        cout<<" (Card Spacing Information not available)";
}

int main()
{
start:
    system("cls");

    cout<<"CREDIT CARD VALIDATOR";

    position str;
	str.x=0;
	str.y=2;

	int no_items=2;
	char menu_items[no_items][260]={"Validate Card No","Exit"};
	int menu_id;

	menu_id=menu(str, menu_items, no_items);

	switch(menu_id)
	{
    case 0:
    {
        system("cls");

        char card_no[20];
        char exp_date[6];

        int exp_mon;
        int exp_yr;

        time_t now = time(0);

        tm *ltm = localtime(&now);
        int curr_yr = 1900 + ltm->tm_year;
        int curr_mon = 1 + ltm->tm_mon;
        int curr_d = ltm->tm_mday;

        cout<<"Current Date: "<<setw(2)<<setfill('0')<<curr_d<<"/"<<setw(2)<<setfill('0')<<curr_mon<<"/"<<curr_yr<<" (DD/MM/YY)";
        cout<<endl<<endl;

        cout<<"Enter Card Number: ";
        cin>>card_no;
        cout<<"Enter Expiry Date(MM/YY): ";
        cin>>exp_date;

        exp_mon=((((int)exp_date[0]-48)*10) + (((int)exp_date[1]-48)));
        exp_yr=((((int)exp_date[3]-48)*10) + (((int)exp_date[4]-48)));

        int checksum;
        if(strlen(card_no)%2==0)
            checksum = calc_checksum_even(card_no);

        else
            checksum = calc_checksum_odd(card_no);

        cout<<endl;

        if(checksum%10 == 0)
        {
            char issu_auth[50];
            strcpy(issu_auth, get_issu_auth(card_no));

            char industry[50];
            strcpy(industry, get_industry(card_no));

            cout<<"Card Number: ";
            print_card_no(card_no, issu_auth);

            int IIN=0;

            int exp = 5;
            for(int i=0; i<6; i++, exp--)
                IIN+=(((int)card_no[i]-48)*(pow(10,exp)));

            cout<<endl<<endl<<"This card is VALID (According to Luhn Algorithm)";

            cout<<endl<<endl<<"Issuer Identification Number (IIN): "<<IIN;
            cout<<endl<<"Major Industry Identifier (MII): "<<card_no[0];
            cout<<endl<<"Personal Account Number: ";

            for(int i=6; i<strlen(card_no)-1; i++)
                cout<<card_no[i];

            cout<<endl<<"Check Digit: "<<card_no[strlen(card_no)-1];


            cout<<endl<<endl<<"Issuing Authority: "<<issu_auth;
            cout<<endl<<"Industry: "<<industry;
            cout<<endl<<"Length: "<<strlen(card_no)<<" digits";


            cout<<endl<<endl<<"Expiry Date(MM/YY): "<<setw(2)<<setfill('0')<<exp_mon<<"/"<<exp_yr;

            curr_yr=curr_yr%100;

            cout<<endl;

            if(exp_yr<curr_yr)
                cout<<"This card has EXPIRED!";

            else if(exp_yr==curr_yr)
            {
                if(exp_mon<curr_mon)
                    cout<<"This card has EXPIRED!";

                else if(exp_mon==curr_mon)
                    cout<<"This card will EXPIRE THIS MONTH!";

                else
                    cout<<"This card has YET NOT EXPIRED!";
            }

            else
                cout<<"This card has YET NOT EXPIRED!";

            cout<<endl<<endl<<"Press any key to return to main menu...";

        }

        else
            cout<<"The card is INVALID (According to Luhn Algorithm)";

        _getch();

        goto start;

    }
    case 1:
            exit(0);
	}

    return 0;
}
