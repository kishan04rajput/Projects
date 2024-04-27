import React, { useEffect, useState } from 'react';

function SearchComponent({ data, setSearchData, pageNumber, setPageNumber, fromPage, setFromPage, toPage, setToPage}) {
const [query, setQuery] = useState('');
const [savedPageNumber, setSavedPageNumber] = useState(pageNumber);
const [savedFromPage, setSavedFromPage] = useState(fromPage);
const [savedToPage, setSavedToPage] = useState(toPage);

const [flag, setFlag] = useState(0);

const handleInputChange = (event) => {
setQuery(event.target.value);
};

useEffect(()=>{
    if(query.length === 0){
        setPageNumber(savedPageNumber);
        setFromPage(savedFromPage);
        setToPage(savedToPage);
        setFlag(0);
    }else if(query.length === 1){
        if(flag === 0){
            setSavedPageNumber(pageNumber);
            setSavedFromPage(fromPage);
            setSavedToPage(toPage);
            setFlag(1);
            setPageNumber(1);
            setFromPage(0);
            setToPage(10);
        }else{
            setFlag(0);
        }
    }
    else{
        setPageNumber(1);
        setFromPage(0);
        setToPage(10);
    }
    handleSearch();
},[query]);

const handleSearch = () => {
if (!query.trim()) {
    setSearchData(data);
} else {
    const filteredData = data.filter(item =>
    item.asset_id.toLowerCase().includes(query.toLowerCase())
    );
    setSearchData(filteredData);
}
};

return (
<div>
    <input type="text" value={query} onChange={handleInputChange} placeholder='Quick search....' id='searchBar'/>
</div>
);
}

export default SearchComponent;
