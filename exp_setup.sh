#1 generate a tor network
scp -r ngnt@10.15.123.121:/chenfeitor/tornetwork/ .
cd tornetwork
unzip top-1m.csv.zip
python ~/shadow-plugin-tor/tools/parsealexa.py
tar xaf server-descriptors-2016-06.tar.xz
tar xaf extra-infos-2016-06.tar.xz
tar xaf consensuses-2016-06.tar.xz
export PATH=${PATH}:~/shadow-plugin-tor/build/tor/src/or:~/shadow-plugin-tor/build/tor/src/tools
mkdir exp1
cd exp1
python ~/shadow-plugin-tor/tools/generate.py --nauths 10 --nrelays 3600 --nclients 13800 --nservers 4000 --fweb 0.90 --fbulk 0.10 --nperf50k 600 --nperf1m 600 --nperf5m 600 ../alexa-top-1000-ips.csv ../2016-06-30-23-00-00-consensus ../server-descriptors-2016-06/ ../extra-infos-2016-06/ ../clients.csv