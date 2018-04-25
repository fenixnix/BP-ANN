_G['os'] = nil
_G['io'] = nil
json = require 'json'
gUser = nil 

function init()
    _InitAnn(2)
end

function setUser(pUser) 
    gUser = pUser 
end

nerve = {
    [0] = 0, --bias
}
lambda = 0.05

function _Sigmoid(inputSignal)
    result = 1.0/(1.0+ math.exp(-1*inputSignal))
    return result
end

function _InitAnn(cnt)
   for i = cnt , 1, -1 do
    nerve[i] = math.random()
   end
end

function _Ask(inputSignal)
    local s = nerve[0]
    s = s + inputSignal[1]*nerve[1]
    s = s + inputSignal[2]*nerve[2]
    return _Sigmoid(s);
end

function _Teach(inputs,outputs)
    local O = _Ask(inputs)
    local E = O*(1.0-O)*(outputs[1]-O)
    nerve[1] = nerve[1]+lambda*E*inputs[1]
    nerve[2] = nerve[2]+lambda*E*inputs[2]
    nerve[0] = nerve[0]+lambda*E
end

function str2hex(pVar)  

    local hexstr  
    local charcode  
    local allhexstr = ''

    local bytes = pVar
  
    for i = 1, string.len(bytes) do  
  
        local charcode = tonumber(string.byte(bytes, i, i));  
        local hexstr = string.format("%02X", charcode);  
  
        allhexstr=allhexstr..hexstr  
    end  

    return allhexstr;  
end  

function hex2str(pVar)  
    local allhexstr = ''
    for i = 1, string.len(pVar) - 1, 2 do  
  
        local doublebytestr = string.sub(pVar, i, i+1);  
        local n = tonumber(doublebytestr, 16);  
        allhexstr=allhexstr..string.format("%c", n)
    end  
  
    return allhexstr
end

--[[
OriginNode Contract Code
{'input':[1,2,3,4]}
--]]
function getAsk(inputString)
    local str = hex2str(inputString)
    local input = json.decode(str)
    local O = _Ask(input['I'])
    return json.encode({output=O})
end

function teach(inputString)
    local str = hex2str(inputString)
    local IO = json.decode(str)
    local O = _Teach(IO['I'],IO['O'])
    return str.." OK!"
end

function getHelp()
    local curTable = {}
    curTable['MethodSet'] = {}
    curTable['MethodSet']['teach'] = {}
    curTable['MethodSet']['teach']['param'] = '{"I":[0,0],"O":[0]}'
    curTable['MethodSet']['teach']['param type'] = 'hex'
    curTable['MethodSet']['teach']['example'] = 'teach {"I":[1,0],"O":[0]}'
    curTable['MethodSet']['teach']['desc'] = '[1,0]/[0] can set any numeric'

    curTable['MethodGet'] = {}
    curTable['MethodGet']['getHelp'] = {}
    curTable['MethodGet']['getHelp']['param'] = 'null'
    curTable['MethodGet']['getHelp']['param type'] = 'normal'
    curTable['MethodGet']['getHelp']['example'] = 'getHelp null'
    curTable['MethodGet']['getHelp']['desc'] = 'return ann contract help'

    curTable['MethodGet']['getAsk'] = {}
    curTable['MethodGet']['getAsk']['param'] = '{"I":[0,0]}'
    curTable['MethodGet']['getAsk']['param type'] = 'hex'
    curTable['MethodGet']['getAsk']['example'] = 'getAsk {"I":[1,0]}'
    curTable['MethodGet']['getAsk']['desc'] = '[1,0] can set any numeric'
    return json.encode(curTable)
end

--[[
SelfTest Code
--]]
function testTeach(times)
    print('Teach And')
    for i = times , 1, -1 
    do  
        _Teach({0,0},{0})
        _Teach({0,1},{0})
        _Teach({1,0},{0})
        _Teach({1,1},{1})
    end
end

function testAsk()
    print('Results:')
    result = _Ask({0,0})
    print(result)
    result = _Ask({0,1})
    print(result)
    result = _Ask({1,0})
    print(result)
    result = _Ask({1,1})
    print(result)
end
