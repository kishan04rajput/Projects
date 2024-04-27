import './App.css';
import axios from 'axios';
import React, { useState, useEffect } from 'react';
import LoadingPage from './pages/LoadingPage';
import SearchComponent from './pages/SearchPage';

function App() {
  const [loading, setLoading] = useState(true);
  const [mergedData, setMergedData] = useState([]);
  const [totalData, setTotalData] = useState(0);
  const [totalPages, setTotalPages] = useState(0);

  const [pageNumber, setPageNumber] = useState(1);
  const [fromPage, setFromPage] = useState(0);
  const [toPage, setToPage] = useState(10);
  const [pageData, setPageData] = useState([]);

  const [searchData, setSearchData] = useState([]);

  useEffect(() => {
    async function fetchData() {
      try {
        const rateResponse = await axios.get('https://rest.coinapi.io/v1/exchangerate/INR', {
          headers: {
            'X-CoinAPI-Key': 'b591e5f0-2af0-4745-bf12-73fa39b2c24c'
          }
        });
        const iconResponse = await axios.get('https://rest.coinapi.io/v1/assets/icons/1', {
          headers: {
            'X-CoinAPI-Key': 'b591e5f0-2af0-4745-bf12-73fa39b2c24c'
          }
        });

        const rateMap = {};
        rateResponse.data.rates.forEach(rate => {
          rateMap[rate.asset_id_quote] = rate.rate;
        });

        const mergedData = iconResponse.data.reduce((result, icon) => {
          const rate = rateMap[icon.asset_id];
          if (rate !== undefined) {
            result.push({
              url: icon.url,
              asset_id: icon.asset_id,
              rate: rate
            });
          }
          return result;
        }, []);

        mergedData.sort((a, b) => {
          if (a.rate < b.rate) return -1;
          if (a.rate > b.rate) return 1;
          return 0;
        });

        setMergedData(mergedData);

        setTotalData(mergedData.length);

        setTimeout(() => {
          setLoading(false);
        }, 1000);
      } catch (error) {
        console.log(error);
      }
    }

    fetchData();
  }, []);

  useEffect(()=>{
    setPageData(searchData.slice(fromPage, toPage));
    // console.log(pageNumber +" "+ fromPage +" "+ toPage);
  },[searchData]);

  useEffect(() => {
    setTotalPages(Math.ceil(totalData/10));
  }, [totalData]);

  useEffect(()=>{
    setPageData(searchData.slice(fromPage, toPage));
    // console.log(pageNumber +" "+ fromPage +" "+ toPage);
  },[fromPage, toPage]);

  function nextPage() {
    if(pageNumber<Math.ceil(searchData.length/10)){
      setPageNumber(prevPageNumber => prevPageNumber + 1);
    }
  }

  function previousPage() {
    if(pageNumber>1){
      setPageNumber(prevPageNumber => prevPageNumber - 1);
    }
  }

  useEffect(()=>{
    setFromPage((pageNumber-1)*10);
    setToPage(((pageNumber-1)*10)+10);
  },[pageNumber]);

  const handlePageNumberChange = (event) => {
    const value = parseInt(event.target.value);
    if (!isNaN(value) && value >= 1 && value <= Math.ceil(searchData.length / 10)) {
      setPageNumber(value);
    }
    if(isNaN(value)){
      setPageNumber();
    }
  };

  if (loading) {
    return <LoadingPage />;
  }
  
  return (
    <div>
      <div className='topPart'>
        <h1>Block Chain Quantifier!</h1>
        <button onClick={previousPage}>Previous</button>
        <span><input
        type="number"
        value={pageNumber}
        onChange={handlePageNumberChange}
        min="1"
        max={Math.ceil(searchData.length / 10)}
        id='pageNumber'
      />/{Math.ceil(searchData.length/10)}</span>
        <button onClick={nextPage}>Next</button>
        <SearchComponent data={mergedData} setSearchData={setSearchData} pageNumber={pageNumber} setPageNumber={setPageNumber} fromPage={fromPage} setFromPage={setFromPage} toPage={toPage} setToPage={setToPage}/>
      </div>

      <table>
        {/* <thead>
          <tr>
            <th>Icon</th>
            <th>Name</th>
            <th>Rate</th>
          </tr>
        </thead> */}
        <tbody>
          {pageData.map(({ url, asset_id, rate }) => (
            <tr key={asset_id}>
              <td style={{textAlign:"right", padding:"0.2% 1%"}}>
                <img src={url} alt={asset_id}  />
              </td>
              <td style={{textAlign:"left"}}>{asset_id}</td>
              <td>{"Rs." +" "+ Math.floor(1 / rate)}</td>
            </tr>
          ))}
        </tbody>
      </table>

    </div>
  );
}

export default App;