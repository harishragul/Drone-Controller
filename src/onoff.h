bool status = false;

int onoff(int ch3, int ch4){
    if (!status && ch3 < 1100 && ch4 < 1100) status = true;
    if (status && ch3 < 1100 && ch4 > 1900) status = false;

    return status;
}