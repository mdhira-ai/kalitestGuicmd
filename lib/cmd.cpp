#include "cmd.h"
#include <QComboBox>
#include <QString>


void cmdcheck::cmdchange(
    const QString &arg1,
    QComboBox *selectcommand,
    QComboBox *subselectcommand
)

{

    if (arg1 == "Basic Scanning Commands")
    {
        subselectcommand->clear();
        subselectcommand->addItems({"-sS (TCP SYN scan)",
                                    "-sT (TCP connect scan)",
                                    "-sU (UDP scan)",
                                    "-sP (Ping scan)",
                                    "-sL (List scan)"});
    }
    else if (arg1 == "Advanced Scanning Techniques")
    {
        subselectcommand->clear();
        subselectcommand->addItems({
            "-sA (ACK scan)",
            "-sW (Window scan)",
            "-sM (TCP Maimon scan)",
            "-sN (TCP Null scan)",
            "-sF (TCP FIN scan)"
            "-p- (Scan all ports)",
            "--top-ports (Scan top ports: 20)" // TODO: add port lineedit
        });
    }
    else if (arg1 == "Script Scanning")
    {
        subselectcommand->clear();
        subselectcommand->addItems({"--script=default",
                                    "--script=vuln",
                                    "--script=discovery",
                                    "--script=safe"});
    }
    else if (arg1 == "Firewall/IDS Evasion")
    {
        subselectcommand->clear();
        subselectcommand->addItems({
            "-f (Fragment packets)",
            "--mtu (Set custom MTU)",
            "-D (Decoy scan)",
            "-S (Spoof source address)",
            "--data-length (Append random data)",
            "-PA (Use TCP ACK packets for discovery)",
            "-PS (Use TCP SYN packets for discovery)",
            "--source-port (Randomize source port)" // TODO:need to add port lineedit
        });
    }
    else if (arg1 == "Service and Vulnerability Detection")
    {
        subselectcommand->clear();
        subselectcommand->addItems({
            "-sV (Service version detection)",
            "--version-intensity",
            "--version-light",
            "--version-all",
            "--script=vuln",
            "-O (OS detection)",
            "-p (Scan for specific services)" // TODO: need to add nmap -p 22,53,110,143 192.168.1.1

        });
    }
    else if (arg1 == "Network Mapping")
    {
        subselectcommand->clear();
        subselectcommand->addItems({"-sn (Ping scan)",
                                    "-PE (ICMP echo request)",
                                    "-PP (ICMP timestamp request)",
                                    "-PM (ICMP address mask request)",
                                    "-PO (Protocol ping)",
                                    "-sL (List targets without scanning)",
                                    "--iflist (Show interfaces and routes) "

        });
    }

    else
    {
        subselectcommand->clear();
    }

}