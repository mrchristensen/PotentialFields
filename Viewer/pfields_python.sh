cd ../MundoVerdadero/SimCode
./sim > simOutput.txt
cd ../../Robot
./robot pfields false > robotOutput.txt
cd ../AgentPython
python3 agentPython.py pfields false > agentOutput.txt
