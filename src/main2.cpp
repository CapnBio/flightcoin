<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE abiword PUBLIC "-//ABISOURCE//DTD AWML 1.0 Strict//EN" "http://www.abisource.com/awml.dtd">
<abiword template="false" xmlns:ct="http://www.abisource.com/changetracking.dtd" xmlns:fo="http://www.w3.org/1999/XSL/Format" xmlns:math="http://www.w3.org/1998/Math/MathML" xid-max="3848" xmlns:dc="http://purl.org/dc/elements/1.1/" fileformat="1.1" xmlns:svg="http://www.w3.org/2000/svg" xmlns:awml="http://www.abisource.com/awml.dtd" xmlns="http://www.abisource.com/awml.dtd" xmlns:xlink="http://www.w3.org/1999/xlink" version="2.9.2" xml:space="preserve" props="dom-dir:ltr; document-footnote-restart-section:0; document-endnote-type:numeric; document-endnote-place-enddoc:1; document-endnote-initial:1; lang:en-US; document-endnote-restart-section:0; document-footnote-restart-page:0; document-footnote-type:numeric; document-footnote-initial:1; document-endnote-place-endsection:0">
<!-- ======================================================================== -->
<!-- This file is an AbiWord document.                                        -->
<!-- AbiWord is a free, Open Source word processor.                           -->
<!-- More information about AbiWord is available at http://www.abisource.com/ -->
<!-- You should not edit this file by hand.                                   -->
<!-- ======================================================================== -->

<metadata>
<m key="abiword.generator">AbiWord</m>
<m key="dc.format">application/x-abiword</m>
</metadata>
<rdf>
</rdf>
<styles>
<s type="P" name="Normal" basedon="" followedby="Current Settings" props="font-family:Liberation Serif; margin-top:0pt; font-variant:normal; margin-left:0pt; text-indent:0in; widows:2; font-style:normal; font-weight:normal; text-decoration:none; color:000000; line-height:1.0; text-align:left; margin-bottom:0pt; text-position:normal; margin-right:0pt; bgcolor:transparent; font-size:12pt; font-stretch:normal"/>
</styles>
<pagesize pagetype="A4" orientation="portrait" width="210.000000" height="297.000000" units="mm" page-scale="1.000000"/>
<section xid="1">
<p style="Normal" xid="2" props="text-align:left; dom-dir:ltr">// Copyright (c) 2009-2010 Satoshi Nakamoto</p>
<p style="Normal" xid="3" props="text-align:left; dom-dir:ltr">// Copyright (c) 2009-2012 The Bitcoin developers</p>
<p style="Normal" xid="4" props="text-align:left; dom-dir:ltr">// Copyright (c) 2011-2012 Litecoin Developers</p>
<p style="Normal" xid="5" props="text-align:left; dom-dir:ltr">// Distributed under the MIT/X11 software license, see the accompanying</p>
<p style="Normal" xid="6" props="text-align:left; dom-dir:ltr">// file COPYING or http://www.opensource.org/licenses/mit-license.php.</p>
<p style="Normal" xid="7"><c></c></p>
<p style="Normal" xid="8" props="text-align:left; dom-dir:ltr">#include "checkpoints.h"</p>
<p style="Normal" xid="9" props="text-align:left; dom-dir:ltr">#include "db.h"</p>
<p style="Normal" xid="10" props="text-align:left; dom-dir:ltr">#include "net.h"</p>
<p style="Normal" xid="11" props="text-align:left; dom-dir:ltr">#include "init.h"</p>
<p style="Normal" xid="12" props="text-align:left; dom-dir:ltr">#include "ui_interface.h"</p>
<p style="Normal" xid="13" props="text-align:left; dom-dir:ltr">#include &lt;boost/algorithm/string/replace.hpp&gt;</p>
<p style="Normal" xid="14" props="text-align:left; dom-dir:ltr">#include &lt;boost/filesystem.hpp&gt;</p>
<p style="Normal" xid="15" props="text-align:left; dom-dir:ltr">#include &lt;boost/filesystem/fstream.hpp&gt;</p>
<p style="Normal" xid="16"><c></c></p>
<p style="Normal" xid="17" props="text-align:left; dom-dir:ltr">using namespace std;</p>
<p style="Normal" xid="18" props="text-align:left; dom-dir:ltr">using namespace boost;</p>
<p style="Normal" xid="19"><c></c></p>
<p style="Normal" xid="20">//</p>
<p style="Normal" xid="21" props="text-align:left; dom-dir:ltr">// Global state</p>
<p style="Normal" xid="22">//</p>
<p style="Normal" xid="23"><c></c></p>
<p style="Normal" xid="24" props="text-align:left; dom-dir:ltr">CCriticalSection cs_setpwalletRegistered;</p>
<p style="Normal" xid="25" props="text-align:left; dom-dir:ltr">set&lt;CWallet*&gt; setpwalletRegistered;</p>
<p style="Normal" xid="26"><c></c></p>
<p style="Normal" xid="27" props="text-align:left; dom-dir:ltr">CCriticalSection cs_main;</p>
<p style="Normal" xid="28"><c></c></p>
<p style="Normal" xid="29" props="text-align:left; dom-dir:ltr">CTxMemPool mempool;</p>
<p style="Normal" xid="30" props="text-align:left; dom-dir:ltr">unsigned int nTransactionsUpdated = 0;</p>
<p style="Normal" xid="31"><c></c></p>
<p style="Normal" xid="32" props="text-align:left; dom-dir:ltr">map&lt;uint256, CBlockIndex*&gt; mapBlockIndex;</p>
<p style="Normal" xid="33" props="text-align:left; dom-dir:ltr">uint256 hashGenesisBlock("0x384b060671f4a93948e9c168216dadb0ca2fbc54aa11c86b0345b6af1c59b2f5");</p>
<p style="Normal" xid="34" props="text-align:left; dom-dir:ltr">static CBigNum bnProofOfWorkLimit(~uint256(0) &gt;&gt; 20); // starting difficulty is 1 / 2^12</p>
<p style="Normal" xid="35" props="text-align:left; dom-dir:ltr">CBlockIndex* pindexGenesisBlock = NULL;</p>
<p style="Normal" xid="36" props="text-align:left; dom-dir:ltr">int nBestHeight = -1;</p>
<p style="Normal" xid="37" props="text-align:left; dom-dir:ltr">CBigNum bnBestChainWork = 0;</p>
<p style="Normal" xid="38" props="text-align:left; dom-dir:ltr">CBigNum bnBestInvalidWork = 0;</p>
<p style="Normal" xid="39" props="text-align:left; dom-dir:ltr">uint256 hashBestChain = 0;</p>
<p style="Normal" xid="40" props="text-align:left; dom-dir:ltr">CBlockIndex* pindexBest = NULL;</p>
<p style="Normal" xid="41" props="text-align:left; dom-dir:ltr">int64 nTimeBestReceived = 0;</p>
<p style="Normal" xid="42"><c></c></p>
<p style="Normal" xid="43" props="text-align:left; dom-dir:ltr">CMedianFilter&lt;int&gt; cPeerBlockCounts(5, 0); // Amount of blocks that other nodes claim to have</p>
<p style="Normal" xid="44"><c></c></p>
<p style="Normal" xid="45" props="text-align:left; dom-dir:ltr">map&lt;uint256, CBlock*&gt; mapOrphanBlocks;</p>
<p style="Normal" xid="46" props="text-align:left; dom-dir:ltr">multimap&lt;uint256, CBlock*&gt; mapOrphanBlocksByPrev;</p>
<p style="Normal" xid="47"><c></c></p>
<p style="Normal" xid="48" props="text-align:left; dom-dir:ltr">map&lt;uint256, CDataStream*&gt; mapOrphanTransactions;</p>
<p style="Normal" xid="49" props="text-align:left; dom-dir:ltr">map&lt;uint256, map&lt;uint256, CDataStream*&gt; &gt; mapOrphanTransactionsByPrev;</p>
<p style="Normal" xid="50"><c></c></p>
<p style="Normal" xid="51" props="text-align:left; dom-dir:ltr">// Constant stuff for coinbase transactions we create:</p>
<p style="Normal" xid="52" props="text-align:left; dom-dir:ltr">CScript COINBASE_FLAGS;</p>
<p style="Normal" xid="53"><c></c></p>
<p style="Normal" xid="54" props="text-align:left; dom-dir:ltr">const string strMessageMagic = "FlightCoin Signed Message:\n";</p>
<p style="Normal" xid="55"><c></c></p>
<p style="Normal" xid="56" props="text-align:left; dom-dir:ltr">double dHashesPerSec;</p>
<p style="Normal" xid="57" props="text-align:left; dom-dir:ltr">int64 nHPSTimerStart;</p>
<p style="Normal" xid="58"><c></c></p>
<p style="Normal" xid="59" props="text-align:left; dom-dir:ltr">// Settings</p>
<p style="Normal" xid="60" props="text-align:left; dom-dir:ltr">int64 nTransactionFee = 0;</p>
<p style="Normal" xid="61" props="text-align:left; dom-dir:ltr">int64 nMinimumInputValue = CENT / 100;</p>
<p style="Normal" xid="62"><c></c></p>
<p style="Normal" xid="63"><c></c></p>
<p style="Normal" xid="64"><c></c></p>
<p style="Normal" xid="65">//////////////////////////////////////////////////////////////////////////////</p>
<p style="Normal" xid="66">//</p>
<p style="Normal" xid="67" props="text-align:left; dom-dir:ltr">// dispatching functions</p>
<p style="Normal" xid="68">//</p>
<p style="Normal" xid="69"><c></c></p>
<p style="Normal" xid="70" props="text-align:left; dom-dir:ltr">// These functions dispatch to one or all registered wallets</p>
<p style="Normal" xid="71"><c></c></p>
<p style="Normal" xid="72"><c></c></p>
<p style="Normal" xid="73" props="text-align:left; dom-dir:ltr">void RegisterWallet(CWallet* pwalletIn)</p>
<p style="Normal" xid="74">{</p>
<p style="Normal" xid="75">    {</p>
<p style="Normal" xid="76" props="text-align:left; dom-dir:ltr">        LOCK(cs_setpwalletRegistered);</p>
<p style="Normal" xid="77" props="text-align:left; dom-dir:ltr">        setpwalletRegistered.insert(pwalletIn);</p>
<p style="Normal" xid="78">    }</p>
<p style="Normal" xid="79">}</p>
<p style="Normal" xid="80"><c></c></p>
<p style="Normal" xid="81" props="text-align:left; dom-dir:ltr">void UnregisterWallet(CWallet* pwalletIn)</p>
<p style="Normal" xid="82">{</p>
<p style="Normal" xid="83">    {</p>
<p style="Normal" xid="84" props="text-align:left; dom-dir:ltr">        LOCK(cs_setpwalletRegistered);</p>
<p style="Normal" xid="85" props="text-align:left; dom-dir:ltr">        setpwalletRegistered.erase(pwalletIn);</p>
<p style="Normal" xid="86">    }</p>
<p style="Normal" xid="87">}</p>
<p style="Normal" xid="88"><c></c></p>
<p style="Normal" xid="89" props="text-align:left; dom-dir:ltr">// check whether the passed transaction is from us</p>
<p style="Normal" xid="90" props="text-align:left; dom-dir:ltr">bool static IsFromMe(CTransaction&amp; tx)</p>
<p style="Normal" xid="91">{</p>
<p style="Normal" xid="92" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(CWallet* pwallet, setpwalletRegistered)</p>
<p style="Normal" xid="93" props="text-align:left; dom-dir:ltr">        if (pwallet-&gt;IsFromMe(tx))</p>
<p style="Normal" xid="94" props="text-align:left; dom-dir:ltr">            return true;</p>
<p style="Normal" xid="95" props="text-align:left; dom-dir:ltr">    return false;</p>
<p style="Normal" xid="96">}</p>
<p style="Normal" xid="97"><c></c></p>
<p style="Normal" xid="98" props="text-align:left; dom-dir:ltr">// get the wallet transaction with the given hash (if it exists)</p>
<p style="Normal" xid="99" props="text-align:left; dom-dir:ltr">bool static GetTransaction(const uint256&amp; hashTx, CWalletTx&amp; wtx)</p>
<p style="Normal" xid="100">{</p>
<p style="Normal" xid="101" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(CWallet* pwallet, setpwalletRegistered)</p>
<p style="Normal" xid="102" props="text-align:left; dom-dir:ltr">        if (pwallet-&gt;GetTransaction(hashTx,wtx))</p>
<p style="Normal" xid="103" props="text-align:left; dom-dir:ltr">            return true;</p>
<p style="Normal" xid="104" props="text-align:left; dom-dir:ltr">    return false;</p>
<p style="Normal" xid="105">}</p>
<p style="Normal" xid="106"><c></c></p>
<p style="Normal" xid="107" props="text-align:left; dom-dir:ltr">// erases transaction with the given hash from all wallets</p>
<p style="Normal" xid="108" props="text-align:left; dom-dir:ltr">void static EraseFromWallets(uint256 hash)</p>
<p style="Normal" xid="109">{</p>
<p style="Normal" xid="110" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(CWallet* pwallet, setpwalletRegistered)</p>
<p style="Normal" xid="111" props="text-align:left; dom-dir:ltr">        pwallet-&gt;EraseFromWallet(hash);</p>
<p style="Normal" xid="112">}</p>
<p style="Normal" xid="113"><c></c></p>
<p style="Normal" xid="114" props="text-align:left; dom-dir:ltr">// make sure all wallets know about the given transaction, in the given block</p>
<p style="Normal" xid="115" props="text-align:left; dom-dir:ltr">void SyncWithWallets(const CTransaction&amp; tx, const CBlock* pblock, bool fUpdate)</p>
<p style="Normal" xid="116">{</p>
<p style="Normal" xid="117" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(CWallet* pwallet, setpwalletRegistered)</p>
<p style="Normal" xid="118" props="text-align:left; dom-dir:ltr">        pwallet-&gt;AddToWalletIfInvolvingMe(tx, pblock, fUpdate);</p>
<p style="Normal" xid="119">}</p>
<p style="Normal" xid="120"><c></c></p>
<p style="Normal" xid="121" props="text-align:left; dom-dir:ltr">// notify wallets about a new best chain</p>
<p style="Normal" xid="122" props="text-align:left; dom-dir:ltr">void static SetBestChain(const CBlockLocator&amp; loc)</p>
<p style="Normal" xid="123">{</p>
<p style="Normal" xid="124" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(CWallet* pwallet, setpwalletRegistered)</p>
<p style="Normal" xid="125" props="text-align:left; dom-dir:ltr">        pwallet-&gt;SetBestChain(loc);</p>
<p style="Normal" xid="126">}</p>
<p style="Normal" xid="127"><c></c></p>
<p style="Normal" xid="128" props="text-align:left; dom-dir:ltr">// notify wallets about an updated transaction</p>
<p style="Normal" xid="129" props="text-align:left; dom-dir:ltr">void static UpdatedTransaction(const uint256&amp; hashTx)</p>
<p style="Normal" xid="130">{</p>
<p style="Normal" xid="131" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(CWallet* pwallet, setpwalletRegistered)</p>
<p style="Normal" xid="132" props="text-align:left; dom-dir:ltr">        pwallet-&gt;UpdatedTransaction(hashTx);</p>
<p style="Normal" xid="133">}</p>
<p style="Normal" xid="134"><c></c></p>
<p style="Normal" xid="135" props="text-align:left; dom-dir:ltr">// dump all wallets</p>
<p style="Normal" xid="136" props="text-align:left; dom-dir:ltr">void static PrintWallets(const CBlock&amp; block)</p>
<p style="Normal" xid="137">{</p>
<p style="Normal" xid="138" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(CWallet* pwallet, setpwalletRegistered)</p>
<p style="Normal" xid="139" props="text-align:left; dom-dir:ltr">        pwallet-&gt;PrintWallet(block);</p>
<p style="Normal" xid="140">}</p>
<p style="Normal" xid="141"><c></c></p>
<p style="Normal" xid="142" props="text-align:left; dom-dir:ltr">// notify wallets about an incoming inventory (for request counts)</p>
<p style="Normal" xid="143" props="text-align:left; dom-dir:ltr">void static Inventory(const uint256&amp; hash)</p>
<p style="Normal" xid="144">{</p>
<p style="Normal" xid="145" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(CWallet* pwallet, setpwalletRegistered)</p>
<p style="Normal" xid="146" props="text-align:left; dom-dir:ltr">        pwallet-&gt;Inventory(hash);</p>
<p style="Normal" xid="147">}</p>
<p style="Normal" xid="148"><c></c></p>
<p style="Normal" xid="149" props="text-align:left; dom-dir:ltr">// ask wallets to resend their transactions</p>
<p style="Normal" xid="150" props="text-align:left; dom-dir:ltr">void static ResendWalletTransactions()</p>
<p style="Normal" xid="151">{</p>
<p style="Normal" xid="152" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(CWallet* pwallet, setpwalletRegistered)</p>
<p style="Normal" xid="153" props="text-align:left; dom-dir:ltr">        pwallet-&gt;ResendWalletTransactions();</p>
<p style="Normal" xid="154">}</p>
<p style="Normal" xid="155"><c></c></p>
<p style="Normal" xid="156"><c></c></p>
<p style="Normal" xid="157"><c></c></p>
<p style="Normal" xid="158"><c></c></p>
<p style="Normal" xid="159"><c></c></p>
<p style="Normal" xid="160"><c></c></p>
<p style="Normal" xid="161"><c></c></p>
<p style="Normal" xid="162">//////////////////////////////////////////////////////////////////////////////</p>
<p style="Normal" xid="163">//</p>
<p style="Normal" xid="164" props="text-align:left; dom-dir:ltr">// mapOrphanTransactions</p>
<p style="Normal" xid="165">//</p>
<p style="Normal" xid="166"><c></c></p>
<p style="Normal" xid="167" props="text-align:left; dom-dir:ltr">bool AddOrphanTx(const CDataStream&amp; vMsg)</p>
<p style="Normal" xid="168">{</p>
<p style="Normal" xid="169" props="text-align:left; dom-dir:ltr">    CTransaction tx;</p>
<p style="Normal" xid="170" props="text-align:left; dom-dir:ltr">    CDataStream(vMsg) &gt;&gt; tx;</p>
<p style="Normal" xid="171" props="text-align:left; dom-dir:ltr">    uint256 hash = tx.GetHash();</p>
<p style="Normal" xid="172" props="text-align:left; dom-dir:ltr">    if (mapOrphanTransactions.count(hash))</p>
<p style="Normal" xid="173" props="text-align:left; dom-dir:ltr">        return false;</p>
<p style="Normal" xid="174"><c></c></p>
<p style="Normal" xid="175" props="text-align:left; dom-dir:ltr">    CDataStream* pvMsg = new CDataStream(vMsg);</p>
<p style="Normal" xid="176"><c></c></p>
<p style="Normal" xid="177" props="text-align:left; dom-dir:ltr">    // Ignore big transactions, to avoid a</p>
<p style="Normal" xid="178" props="text-align:left; dom-dir:ltr">    // send-big-orphans memory exhaustion attack. If a peer has a legitimate</p>
<p style="Normal" xid="179" props="text-align:left; dom-dir:ltr">    // large transaction with a missing parent then we assume</p>
<p style="Normal" xid="180" props="text-align:left; dom-dir:ltr">    // it will rebroadcast it later, after the parent transaction(s)</p>
<p style="Normal" xid="181" props="text-align:left; dom-dir:ltr">    // have been mined or received.</p>
<p style="Normal" xid="182" props="text-align:left; dom-dir:ltr">    // 10,000 orphans, each of which is at most 5,000 bytes big is</p>
<p style="Normal" xid="183" props="text-align:left; dom-dir:ltr">    // at most 500 megabytes of orphans:</p>
<p style="Normal" xid="184" props="text-align:left; dom-dir:ltr">    if (pvMsg-&gt;size() &gt; 5000)</p>
<p style="Normal" xid="185">    {</p>
<p style="Normal" xid="186" props="text-align:left; dom-dir:ltr">        printf("ignoring large orphan tx (size: %u, hash: %s)\n", pvMsg-&gt;size(), hash.ToString().substr(0,10).c_str());</p>
<p style="Normal" xid="187" props="text-align:left; dom-dir:ltr">        delete pvMsg;</p>
<p style="Normal" xid="188" props="text-align:left; dom-dir:ltr">        return false;</p>
<p style="Normal" xid="189">    }</p>
<p style="Normal" xid="190"><c></c></p>
<p style="Normal" xid="191" props="text-align:left; dom-dir:ltr">    mapOrphanTransactions[hash] = pvMsg;</p>
<p style="Normal" xid="192" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(const CTxIn&amp; txin, tx.vin)</p>
<p style="Normal" xid="193" props="text-align:left; dom-dir:ltr">        mapOrphanTransactionsByPrev[txin.prevout.hash].insert(make_pair(hash, pvMsg));</p>
<p style="Normal" xid="194"><c></c></p>
<p style="Normal" xid="195" props="text-align:left; dom-dir:ltr">    printf("stored orphan tx %s (mapsz %u)\n", hash.ToString().substr(0,10).c_str(),</p>
<p style="Normal" xid="196" props="text-align:left; dom-dir:ltr">        mapOrphanTransactions.size());</p>
<p style="Normal" xid="197" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="198">}</p>
<p style="Normal" xid="199"><c></c></p>
<p style="Normal" xid="200" props="text-align:left; dom-dir:ltr">void static EraseOrphanTx(uint256 hash)</p>
<p style="Normal" xid="201">{</p>
<p style="Normal" xid="202" props="text-align:left; dom-dir:ltr">    if (!mapOrphanTransactions.count(hash))</p>
<p style="Normal" xid="203" props="text-align:left; dom-dir:ltr">        return;</p>
<p style="Normal" xid="204" props="text-align:left; dom-dir:ltr">    const CDataStream* pvMsg = mapOrphanTransactions[hash];</p>
<p style="Normal" xid="205" props="text-align:left; dom-dir:ltr">    CTransaction tx;</p>
<p style="Normal" xid="206" props="text-align:left; dom-dir:ltr">    CDataStream(*pvMsg) &gt;&gt; tx;</p>
<p style="Normal" xid="207" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(const CTxIn&amp; txin, tx.vin)</p>
<p style="Normal" xid="208">    {</p>
<p style="Normal" xid="209" props="text-align:left; dom-dir:ltr">        mapOrphanTransactionsByPrev[txin.prevout.hash].erase(hash);</p>
<p style="Normal" xid="210" props="text-align:left; dom-dir:ltr">        if (mapOrphanTransactionsByPrev[txin.prevout.hash].empty())</p>
<p style="Normal" xid="211" props="text-align:left; dom-dir:ltr">            mapOrphanTransactionsByPrev.erase(txin.prevout.hash);</p>
<p style="Normal" xid="212">    }</p>
<p style="Normal" xid="213" props="text-align:left; dom-dir:ltr">    delete pvMsg;</p>
<p style="Normal" xid="214" props="text-align:left; dom-dir:ltr">    mapOrphanTransactions.erase(hash);</p>
<p style="Normal" xid="215">}</p>
<p style="Normal" xid="216"><c></c></p>
<p style="Normal" xid="217" props="text-align:left; dom-dir:ltr">unsigned int LimitOrphanTxSize(unsigned int nMaxOrphans)</p>
<p style="Normal" xid="218">{</p>
<p style="Normal" xid="219" props="text-align:left; dom-dir:ltr">    unsigned int nEvicted = 0;</p>
<p style="Normal" xid="220" props="text-align:left; dom-dir:ltr">    while (mapOrphanTransactions.size() &gt; nMaxOrphans)</p>
<p style="Normal" xid="221">    {</p>
<p style="Normal" xid="222" props="text-align:left; dom-dir:ltr">        // Evict a random orphan:</p>
<p style="Normal" xid="223" props="text-align:left; dom-dir:ltr">        uint256 randomhash = GetRandHash();</p>
<p style="Normal" xid="224" props="text-align:left; dom-dir:ltr">        map&lt;uint256, CDataStream*&gt;::iterator it = mapOrphanTransactions.lower_bound(randomhash);</p>
<p style="Normal" xid="225" props="text-align:left; dom-dir:ltr">        if (it == mapOrphanTransactions.end())</p>
<p style="Normal" xid="226" props="text-align:left; dom-dir:ltr">            it = mapOrphanTransactions.begin();</p>
<p style="Normal" xid="227" props="text-align:left; dom-dir:ltr">        EraseOrphanTx(it-&gt;first);</p>
<p style="Normal" xid="228" props="text-align:left; dom-dir:ltr">        ++nEvicted;</p>
<p style="Normal" xid="229">    }</p>
<p style="Normal" xid="230" props="text-align:left; dom-dir:ltr">    return nEvicted;</p>
<p style="Normal" xid="231">}</p>
<p style="Normal" xid="232"><c></c></p>
<p style="Normal" xid="233"><c></c></p>
<p style="Normal" xid="234"><c></c></p>
<p style="Normal" xid="235"><c></c></p>
<p style="Normal" xid="236"><c></c></p>
<p style="Normal" xid="237"><c></c></p>
<p style="Normal" xid="238"><c></c></p>
<p style="Normal" xid="239">//////////////////////////////////////////////////////////////////////////////</p>
<p style="Normal" xid="240">//</p>
<p style="Normal" xid="241" props="text-align:left; dom-dir:ltr">// CTransaction and CTxIndex</p>
<p style="Normal" xid="242">//</p>
<p style="Normal" xid="243"><c></c></p>
<p style="Normal" xid="244" props="text-align:left; dom-dir:ltr">bool CTransaction::ReadFromDisk(CTxDB&amp; txdb, COutPoint prevout, CTxIndex&amp; txindexRet)</p>
<p style="Normal" xid="245">{</p>
<p style="Normal" xid="246" props="text-align:left; dom-dir:ltr">    SetNull();</p>
<p style="Normal" xid="247" props="text-align:left; dom-dir:ltr">    if (!txdb.ReadTxIndex(prevout.hash, txindexRet))</p>
<p style="Normal" xid="248" props="text-align:left; dom-dir:ltr">        return false;</p>
<p style="Normal" xid="249" props="text-align:left; dom-dir:ltr">    if (!ReadFromDisk(txindexRet.pos))</p>
<p style="Normal" xid="250" props="text-align:left; dom-dir:ltr">        return false;</p>
<p style="Normal" xid="251" props="text-align:left; dom-dir:ltr">    if (prevout.n &gt;= vout.size())</p>
<p style="Normal" xid="252">    {</p>
<p style="Normal" xid="253" props="text-align:left; dom-dir:ltr">        SetNull();</p>
<p style="Normal" xid="254" props="text-align:left; dom-dir:ltr">        return false;</p>
<p style="Normal" xid="255">    }</p>
<p style="Normal" xid="256" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="257">}</p>
<p style="Normal" xid="258"><c></c></p>
<p style="Normal" xid="259" props="text-align:left; dom-dir:ltr">bool CTransaction::ReadFromDisk(CTxDB&amp; txdb, COutPoint prevout)</p>
<p style="Normal" xid="260">{</p>
<p style="Normal" xid="261" props="text-align:left; dom-dir:ltr">    CTxIndex txindex;</p>
<p style="Normal" xid="262" props="text-align:left; dom-dir:ltr">    return ReadFromDisk(txdb, prevout, txindex);</p>
<p style="Normal" xid="263">}</p>
<p style="Normal" xid="264"><c></c></p>
<p style="Normal" xid="265" props="text-align:left; dom-dir:ltr">bool CTransaction::ReadFromDisk(COutPoint prevout)</p>
<p style="Normal" xid="266">{</p>
<p style="Normal" xid="267" props="text-align:left; dom-dir:ltr">    CTxDB txdb("r");</p>
<p style="Normal" xid="268" props="text-align:left; dom-dir:ltr">    CTxIndex txindex;</p>
<p style="Normal" xid="269" props="text-align:left; dom-dir:ltr">    return ReadFromDisk(txdb, prevout, txindex);</p>
<p style="Normal" xid="270">}</p>
<p style="Normal" xid="271"><c></c></p>
<p style="Normal" xid="272" props="text-align:left; dom-dir:ltr">bool CTransaction::IsStandard() const</p>
<p style="Normal" xid="273">{</p>
<p style="Normal" xid="274" props="text-align:left; dom-dir:ltr">    if (nVersion &gt; CTransaction::CURRENT_VERSION)</p>
<p style="Normal" xid="275" props="text-align:left; dom-dir:ltr">        return false;</p>
<p style="Normal" xid="276"><c></c></p>
<p style="Normal" xid="277" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(const CTxIn&amp; txin, vin)</p>
<p style="Normal" xid="278">    {</p>
<p style="Normal" xid="279" props="text-align:left; dom-dir:ltr">        // Biggest 'standard' txin is a 3-signature 3-of-3 CHECKMULTISIG</p>
<p style="Normal" xid="280" props="text-align:left; dom-dir:ltr">        // pay-to-script-hash, which is 3 ~80-byte signatures, 3</p>
<p style="Normal" xid="281" props="text-align:left; dom-dir:ltr">        // ~65-byte public keys, plus a few script ops.</p>
<p style="Normal" xid="282" props="text-align:left; dom-dir:ltr">        if (txin.scriptSig.size() &gt; 500)</p>
<p style="Normal" xid="283" props="text-align:left; dom-dir:ltr">            return false;</p>
<p style="Normal" xid="284" props="text-align:left; dom-dir:ltr">        if (!txin.scriptSig.IsPushOnly())</p>
<p style="Normal" xid="285" props="text-align:left; dom-dir:ltr">            return false;</p>
<p style="Normal" xid="286">    }</p>
<p style="Normal" xid="287" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(const CTxOut&amp; txout, vout)</p>
<p style="Normal" xid="288" props="text-align:left; dom-dir:ltr">        if (!::IsStandard(txout.scriptPubKey))</p>
<p style="Normal" xid="289" props="text-align:left; dom-dir:ltr">            return false;</p>
<p style="Normal" xid="290" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="291">}</p>
<p style="Normal" xid="292"><c></c></p>
<p style="Normal" xid="293">//</p>
<p style="Normal" xid="294" props="text-align:left; dom-dir:ltr">// Check transaction inputs, and make sure any</p>
<p style="Normal" xid="295" props="text-align:left; dom-dir:ltr">// pay-to-script-hash transactions are evaluating IsStandard scripts</p>
<p style="Normal" xid="296">//</p>
<p style="Normal" xid="297" props="text-align:left; dom-dir:ltr">// Why bother? To avoid denial-of-service attacks; an attacker</p>
<p style="Normal" xid="298" props="text-align:left; dom-dir:ltr">// can submit a standard HASH... OP_EQUAL transaction,</p>
<p style="Normal" xid="299" props="text-align:left; dom-dir:ltr">// which will get accepted into blocks. The redemption</p>
<p style="Normal" xid="300" props="text-align:left; dom-dir:ltr">// script can be anything; an attacker could use a very</p>
<p style="Normal" xid="301" props="text-align:left; dom-dir:ltr">// expensive-to-check-upon-redemption script like:</p>
<p style="Normal" xid="302" props="text-align:left; dom-dir:ltr">//   DUP CHECKSIG DROP ... repeated 100 times... OP_1</p>
<p style="Normal" xid="303">//</p>
<p style="Normal" xid="304" props="text-align:left; dom-dir:ltr">bool CTransaction::AreInputsStandard(const MapPrevTx&amp; mapInputs) const</p>
<p style="Normal" xid="305">{</p>
<p style="Normal" xid="306" props="text-align:left; dom-dir:ltr">    if (IsCoinBase())</p>
<p style="Normal" xid="307" props="text-align:left; dom-dir:ltr">        return true; // Coinbases don't use vin normally</p>
<p style="Normal" xid="308"><c></c></p>
<p style="Normal" xid="309" props="text-align:left; dom-dir:ltr">    for (unsigned int i = 0; i &lt; vin.size(); i++)</p>
<p style="Normal" xid="310">    {</p>
<p style="Normal" xid="311" props="text-align:left; dom-dir:ltr">        const CTxOut&amp; prev = GetOutputFor(vin[i], mapInputs);</p>
<p style="Normal" xid="312"><c></c></p>
<p style="Normal" xid="313" props="text-align:left; dom-dir:ltr">        vector&lt;vector&lt;unsigned char&gt; &gt; vSolutions;</p>
<p style="Normal" xid="314" props="text-align:left; dom-dir:ltr">        txnouttype whichType;</p>
<p style="Normal" xid="315" props="text-align:left; dom-dir:ltr">        // get the scriptPubKey corresponding to this input:</p>
<p style="Normal" xid="316" props="text-align:left; dom-dir:ltr">        const CScript&amp; prevScript = prev.scriptPubKey;</p>
<p style="Normal" xid="317" props="text-align:left; dom-dir:ltr">        if (!Solver(prevScript, whichType, vSolutions))</p>
<p style="Normal" xid="318" props="text-align:left; dom-dir:ltr">            return false;</p>
<p style="Normal" xid="319" props="text-align:left; dom-dir:ltr">        int nArgsExpected = ScriptSigArgsExpected(whichType, vSolutions);</p>
<p style="Normal" xid="320" props="text-align:left; dom-dir:ltr">        if (nArgsExpected &lt; 0)</p>
<p style="Normal" xid="321" props="text-align:left; dom-dir:ltr">            return false;</p>
<p style="Normal" xid="322"><c></c></p>
<p style="Normal" xid="323" props="text-align:left; dom-dir:ltr">        // Transactions with extra stuff in their scriptSigs are</p>
<p style="Normal" xid="324" props="text-align:left; dom-dir:ltr">        // non-standard. Note that this EvalScript() call will</p>
<p style="Normal" xid="325" props="text-align:left; dom-dir:ltr">        // be quick, because if there are any operations</p>
<p style="Normal" xid="326" props="text-align:left; dom-dir:ltr">        // beside "push data" in the scriptSig the</p>
<p style="Normal" xid="327" props="text-align:left; dom-dir:ltr">        // IsStandard() call returns false</p>
<p style="Normal" xid="328" props="text-align:left; dom-dir:ltr">        vector&lt;vector&lt;unsigned char&gt; &gt; stack;</p>
<p style="Normal" xid="329" props="text-align:left; dom-dir:ltr">        if (!EvalScript(stack, vin[i].scriptSig, *this, i, 0))</p>
<p style="Normal" xid="330" props="text-align:left; dom-dir:ltr">            return false;</p>
<p style="Normal" xid="331"><c></c></p>
<p style="Normal" xid="332" props="text-align:left; dom-dir:ltr">        if (whichType == TX_SCRIPTHASH)</p>
<p style="Normal" xid="333">        {</p>
<p style="Normal" xid="334" props="text-align:left; dom-dir:ltr">            if (stack.empty())</p>
<p style="Normal" xid="335" props="text-align:left; dom-dir:ltr">                return false;</p>
<p style="Normal" xid="336" props="text-align:left; dom-dir:ltr">            CScript subscript(stack.back().begin(), stack.back().end());</p>
<p style="Normal" xid="337" props="text-align:left; dom-dir:ltr">            vector&lt;vector&lt;unsigned char&gt; &gt; vSolutions2;</p>
<p style="Normal" xid="338" props="text-align:left; dom-dir:ltr">            txnouttype whichType2;</p>
<p style="Normal" xid="339" props="text-align:left; dom-dir:ltr">            if (!Solver(subscript, whichType2, vSolutions2))</p>
<p style="Normal" xid="340" props="text-align:left; dom-dir:ltr">                return false;</p>
<p style="Normal" xid="341" props="text-align:left; dom-dir:ltr">            if (whichType2 == TX_SCRIPTHASH)</p>
<p style="Normal" xid="342" props="text-align:left; dom-dir:ltr">                return false;</p>
<p style="Normal" xid="343"><c></c></p>
<p style="Normal" xid="344" props="text-align:left; dom-dir:ltr">            int tmpExpected;</p>
<p style="Normal" xid="345" props="text-align:left; dom-dir:ltr">            tmpExpected = ScriptSigArgsExpected(whichType2, vSolutions2);</p>
<p style="Normal" xid="346" props="text-align:left; dom-dir:ltr">            if (tmpExpected &lt; 0)</p>
<p style="Normal" xid="347" props="text-align:left; dom-dir:ltr">                return false;</p>
<p style="Normal" xid="348" props="text-align:left; dom-dir:ltr">            nArgsExpected += tmpExpected;</p>
<p style="Normal" xid="349">        }</p>
<p style="Normal" xid="350"><c></c></p>
<p style="Normal" xid="351" props="text-align:left; dom-dir:ltr">        if (stack.size() != (unsigned int)nArgsExpected)</p>
<p style="Normal" xid="352" props="text-align:left; dom-dir:ltr">            return false;</p>
<p style="Normal" xid="353">    }</p>
<p style="Normal" xid="354"><c></c></p>
<p style="Normal" xid="355" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="356">}</p>
<p style="Normal" xid="357"><c></c></p>
<p style="Normal" xid="358" props="text-align:left; dom-dir:ltr">unsigned int</p>
<p style="Normal" xid="359" props="text-align:left; dom-dir:ltr">CTransaction::GetLegacySigOpCount() const</p>
<p style="Normal" xid="360">{</p>
<p style="Normal" xid="361" props="text-align:left; dom-dir:ltr">    unsigned int nSigOps = 0;</p>
<p style="Normal" xid="362" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(const CTxIn&amp; txin, vin)</p>
<p style="Normal" xid="363">    {</p>
<p style="Normal" xid="364" props="text-align:left; dom-dir:ltr">        nSigOps += txin.scriptSig.GetSigOpCount(false);</p>
<p style="Normal" xid="365">    }</p>
<p style="Normal" xid="366" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(const CTxOut&amp; txout, vout)</p>
<p style="Normal" xid="367">    {</p>
<p style="Normal" xid="368" props="text-align:left; dom-dir:ltr">        nSigOps += txout.scriptPubKey.GetSigOpCount(false);</p>
<p style="Normal" xid="369">    }</p>
<p style="Normal" xid="370" props="text-align:left; dom-dir:ltr">    return nSigOps;</p>
<p style="Normal" xid="371">}</p>
<p style="Normal" xid="372"><c></c></p>
<p style="Normal" xid="373"><c></c></p>
<p style="Normal" xid="374" props="text-align:left; dom-dir:ltr">int CMerkleTx::SetMerkleBranch(const CBlock* pblock)</p>
<p style="Normal" xid="375">{</p>
<p style="Normal" xid="376" props="text-align:left; dom-dir:ltr">    if (fClient)</p>
<p style="Normal" xid="377">    {</p>
<p style="Normal" xid="378" props="text-align:left; dom-dir:ltr">        if (hashBlock == 0)</p>
<p style="Normal" xid="379" props="text-align:left; dom-dir:ltr">            return 0;</p>
<p style="Normal" xid="380">    }</p>
<p style="Normal" xid="381" props="text-align:left; dom-dir:ltr">    else</p>
<p style="Normal" xid="382">    {</p>
<p style="Normal" xid="383" props="text-align:left; dom-dir:ltr">        CBlock blockTmp;</p>
<p style="Normal" xid="384" props="text-align:left; dom-dir:ltr">        if (pblock == NULL)</p>
<p style="Normal" xid="385">        {</p>
<p style="Normal" xid="386" props="text-align:left; dom-dir:ltr">            // Load the block this tx is in</p>
<p style="Normal" xid="387" props="text-align:left; dom-dir:ltr">            CTxIndex txindex;</p>
<p style="Normal" xid="388" props="text-align:left; dom-dir:ltr">            if (!CTxDB("r").ReadTxIndex(GetHash(), txindex))</p>
<p style="Normal" xid="389" props="text-align:left; dom-dir:ltr">                return 0;</p>
<p style="Normal" xid="390" props="text-align:left; dom-dir:ltr">            if (!blockTmp.ReadFromDisk(txindex.pos.nFile, txindex.pos.nBlockPos))</p>
<p style="Normal" xid="391" props="text-align:left; dom-dir:ltr">                return 0;</p>
<p style="Normal" xid="392" props="text-align:left; dom-dir:ltr">            pblock = &amp;blockTmp;</p>
<p style="Normal" xid="393">        }</p>
<p style="Normal" xid="394"><c></c></p>
<p style="Normal" xid="395" props="text-align:left; dom-dir:ltr">        // Update the tx's hashBlock</p>
<p style="Normal" xid="396" props="text-align:left; dom-dir:ltr">        hashBlock = pblock-&gt;GetHash();</p>
<p style="Normal" xid="397"><c></c></p>
<p style="Normal" xid="398" props="text-align:left; dom-dir:ltr">        // Locate the transaction</p>
<p style="Normal" xid="399" props="text-align:left; dom-dir:ltr">        for (nIndex = 0; nIndex &lt; (int)pblock-&gt;vtx.size(); nIndex++)</p>
<p style="Normal" xid="400" props="text-align:left; dom-dir:ltr">            if (pblock-&gt;vtx[nIndex] == *(CTransaction*)this)</p>
<p style="Normal" xid="401" props="text-align:left; dom-dir:ltr">                break;</p>
<p style="Normal" xid="402" props="text-align:left; dom-dir:ltr">        if (nIndex == (int)pblock-&gt;vtx.size())</p>
<p style="Normal" xid="403">        {</p>
<p style="Normal" xid="404" props="text-align:left; dom-dir:ltr">            vMerkleBranch.clear();</p>
<p style="Normal" xid="405" props="text-align:left; dom-dir:ltr">            nIndex = -1;</p>
<p style="Normal" xid="406" props="text-align:left; dom-dir:ltr">            printf("ERROR: SetMerkleBranch() : couldn't find tx in block\n");</p>
<p style="Normal" xid="407" props="text-align:left; dom-dir:ltr">            return 0;</p>
<p style="Normal" xid="408">        }</p>
<p style="Normal" xid="409"><c></c></p>
<p style="Normal" xid="410" props="text-align:left; dom-dir:ltr">        // Fill in merkle branch</p>
<p style="Normal" xid="411" props="text-align:left; dom-dir:ltr">        vMerkleBranch = pblock-&gt;GetMerkleBranch(nIndex);</p>
<p style="Normal" xid="412">    }</p>
<p style="Normal" xid="413"><c></c></p>
<p style="Normal" xid="414" props="text-align:left; dom-dir:ltr">    // Is the tx in a block that's in the main chain</p>
<p style="Normal" xid="415" props="text-align:left; dom-dir:ltr">    map&lt;uint256, CBlockIndex*&gt;::iterator mi = mapBlockIndex.find(hashBlock);</p>
<p style="Normal" xid="416" props="text-align:left; dom-dir:ltr">    if (mi == mapBlockIndex.end())</p>
<p style="Normal" xid="417" props="text-align:left; dom-dir:ltr">        return 0;</p>
<p style="Normal" xid="418" props="text-align:left; dom-dir:ltr">    CBlockIndex* pindex = (*mi).second;</p>
<p style="Normal" xid="419" props="text-align:left; dom-dir:ltr">    if (!pindex || !pindex-&gt;IsInMainChain())</p>
<p style="Normal" xid="420" props="text-align:left; dom-dir:ltr">        return 0;</p>
<p style="Normal" xid="421"><c></c></p>
<p style="Normal" xid="422" props="text-align:left; dom-dir:ltr">    return pindexBest-&gt;nHeight - pindex-&gt;nHeight + 1;</p>
<p style="Normal" xid="423">}</p>
<p style="Normal" xid="424"><c></c></p>
<p style="Normal" xid="425"><c></c></p>
<p style="Normal" xid="426"><c></c></p>
<p style="Normal" xid="427"><c></c></p>
<p style="Normal" xid="428"><c></c></p>
<p style="Normal" xid="429"><c></c></p>
<p style="Normal" xid="430"><c></c></p>
<p style="Normal" xid="431" props="text-align:left; dom-dir:ltr">bool CTransaction::CheckTransaction() const</p>
<p style="Normal" xid="432">{</p>
<p style="Normal" xid="433" props="text-align:left; dom-dir:ltr">    // Basic checks that don't depend on any context</p>
<p style="Normal" xid="434" props="text-align:left; dom-dir:ltr">    if (vin.empty())</p>
<p style="Normal" xid="435" props="text-align:left; dom-dir:ltr">        return DoS(10, error("CTransaction::CheckTransaction() : vin empty"));</p>
<p style="Normal" xid="436" props="text-align:left; dom-dir:ltr">    if (vout.empty())</p>
<p style="Normal" xid="437" props="text-align:left; dom-dir:ltr">        return DoS(10, error("CTransaction::CheckTransaction() : vout empty"));</p>
<p style="Normal" xid="438" props="text-align:left; dom-dir:ltr">    // Size limits</p>
<p style="Normal" xid="439" props="text-align:left; dom-dir:ltr">    if (::GetSerializeSize(*this, SER_NETWORK, PROTOCOL_VERSION) &gt; MAX_BLOCK_SIZE)</p>
<p style="Normal" xid="440" props="text-align:left; dom-dir:ltr">        return DoS(100, error("CTransaction::CheckTransaction() : size limits failed"));</p>
<p style="Normal" xid="441"><c></c></p>
<p style="Normal" xid="442" props="text-align:left; dom-dir:ltr">    // Check for negative or overflow output values</p>
<p style="Normal" xid="443" props="text-align:left; dom-dir:ltr">    int64 nValueOut = 0;</p>
<p style="Normal" xid="444" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(const CTxOut&amp; txout, vout)</p>
<p style="Normal" xid="445">    {</p>
<p style="Normal" xid="446" props="text-align:left; dom-dir:ltr">        if (txout.nValue &lt; 0)</p>
<p style="Normal" xid="447" props="text-align:left; dom-dir:ltr">            return DoS(100, error("CTransaction::CheckTransaction() : txout.nValue negative"));</p>
<p style="Normal" xid="448" props="text-align:left; dom-dir:ltr">        if (txout.nValue &gt; MAX_MONEY)</p>
<p style="Normal" xid="449" props="text-align:left; dom-dir:ltr">            return DoS(100, error("CTransaction::CheckTransaction() : txout.nValue too high"));</p>
<p style="Normal" xid="450" props="text-align:left; dom-dir:ltr">        nValueOut += txout.nValue;</p>
<p style="Normal" xid="451" props="text-align:left; dom-dir:ltr">        if (!MoneyRange(nValueOut))</p>
<p style="Normal" xid="452" props="text-align:left; dom-dir:ltr">            return DoS(100, error("CTransaction::CheckTransaction() : txout total out of range"));</p>
<p style="Normal" xid="453">    }</p>
<p style="Normal" xid="454"><c></c></p>
<p style="Normal" xid="455" props="text-align:left; dom-dir:ltr">    // Check for duplicate inputs</p>
<p style="Normal" xid="456" props="text-align:left; dom-dir:ltr">    set&lt;COutPoint&gt; vInOutPoints;</p>
<p style="Normal" xid="457" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(const CTxIn&amp; txin, vin)</p>
<p style="Normal" xid="458">    {</p>
<p style="Normal" xid="459" props="text-align:left; dom-dir:ltr">        if (vInOutPoints.count(txin.prevout))</p>
<p style="Normal" xid="460" props="text-align:left; dom-dir:ltr">            return false;</p>
<p style="Normal" xid="461" props="text-align:left; dom-dir:ltr">        vInOutPoints.insert(txin.prevout);</p>
<p style="Normal" xid="462">    }</p>
<p style="Normal" xid="463"><c></c></p>
<p style="Normal" xid="464" props="text-align:left; dom-dir:ltr">    if (IsCoinBase())</p>
<p style="Normal" xid="465">    {</p>
<p style="Normal" xid="466" props="text-align:left; dom-dir:ltr">        if (vin[0].scriptSig.size() &lt; 2 || vin[0].scriptSig.size() &gt; 100)</p>
<p style="Normal" xid="467" props="text-align:left; dom-dir:ltr">            return DoS(100, error("CTransaction::CheckTransaction() : coinbase script size"));</p>
<p style="Normal" xid="468">    }</p>
<p style="Normal" xid="469" props="text-align:left; dom-dir:ltr">    else</p>
<p style="Normal" xid="470">    {</p>
<p style="Normal" xid="471" props="text-align:left; dom-dir:ltr">        BOOST_FOREACH(const CTxIn&amp; txin, vin)</p>
<p style="Normal" xid="472" props="text-align:left; dom-dir:ltr">            if (txin.prevout.IsNull())</p>
<p style="Normal" xid="473" props="text-align:left; dom-dir:ltr">                return DoS(10, error("CTransaction::CheckTransaction() : prevout is null"));</p>
<p style="Normal" xid="474">    }</p>
<p style="Normal" xid="475"><c></c></p>
<p style="Normal" xid="476" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="477">}</p>
<p style="Normal" xid="478"><c></c></p>
<p style="Normal" xid="479" props="text-align:left; dom-dir:ltr">bool CTxMemPool::accept(CTxDB&amp; txdb, CTransaction &amp;tx, bool fCheckInputs,</p>
<p style="Normal" xid="480" props="text-align:left; dom-dir:ltr">                        bool* pfMissingInputs)</p>
<p style="Normal" xid="481">{</p>
<p style="Normal" xid="482" props="text-align:left; dom-dir:ltr">    if (pfMissingInputs)</p>
<p style="Normal" xid="483" props="text-align:left; dom-dir:ltr">        *pfMissingInputs = false;</p>
<p style="Normal" xid="484"><c></c></p>
<p style="Normal" xid="485" props="text-align:left; dom-dir:ltr">    if (!tx.CheckTransaction())</p>
<p style="Normal" xid="486" props="text-align:left; dom-dir:ltr">        return error("CTxMemPool::accept() : CheckTransaction failed");</p>
<p style="Normal" xid="487"><c></c></p>
<p style="Normal" xid="488" props="text-align:left; dom-dir:ltr">    // Coinbase is only valid in a block, not as a loose transaction</p>
<p style="Normal" xid="489" props="text-align:left; dom-dir:ltr">    if (tx.IsCoinBase())</p>
<p style="Normal" xid="490" props="text-align:left; dom-dir:ltr">        return tx.DoS(100, error("CTxMemPool::accept() : coinbase as individual tx"));</p>
<p style="Normal" xid="491"><c></c></p>
<p style="Normal" xid="492" props="text-align:left; dom-dir:ltr">    // To help v0.1.5 clients who would see it as a negative number</p>
<p style="Normal" xid="493" props="text-align:left; dom-dir:ltr">    if ((int64)tx.nLockTime &gt; std::numeric_limits&lt;int&gt;::max())</p>
<p style="Normal" xid="494" props="text-align:left; dom-dir:ltr">        return error("CTxMemPool::accept() : not accepting nLockTime beyond 2038 yet");</p>
<p style="Normal" xid="495"><c></c></p>
<p style="Normal" xid="496" props="text-align:left; dom-dir:ltr">    // Rather not work on nonstandard transactions (unless -testnet)</p>
<p style="Normal" xid="497" props="text-align:left; dom-dir:ltr">    if (!fTestNet &amp;&amp; !tx.IsStandard())</p>
<p style="Normal" xid="498" props="text-align:left; dom-dir:ltr">        return error("CTxMemPool::accept() : nonstandard transaction type");</p>
<p style="Normal" xid="499"><c></c></p>
<p style="Normal" xid="500" props="text-align:left; dom-dir:ltr">    // Do we already have it?</p>
<p style="Normal" xid="501" props="text-align:left; dom-dir:ltr">    uint256 hash = tx.GetHash();</p>
<p style="Normal" xid="502">    {</p>
<p style="Normal" xid="503" props="text-align:left; dom-dir:ltr">        LOCK(cs);</p>
<p style="Normal" xid="504" props="text-align:left; dom-dir:ltr">        if (mapTx.count(hash))</p>
<p style="Normal" xid="505" props="text-align:left; dom-dir:ltr">            return false;</p>
<p style="Normal" xid="506">    }</p>
<p style="Normal" xid="507" props="text-align:left; dom-dir:ltr">    if (fCheckInputs)</p>
<p style="Normal" xid="508" props="text-align:left; dom-dir:ltr">        if (txdb.ContainsTx(hash))</p>
<p style="Normal" xid="509" props="text-align:left; dom-dir:ltr">            return false;</p>
<p style="Normal" xid="510"><c></c></p>
<p style="Normal" xid="511" props="text-align:left; dom-dir:ltr">    // Check for conflicts with in-memory transactions</p>
<p style="Normal" xid="512" props="text-align:left; dom-dir:ltr">    CTransaction* ptxOld = NULL;</p>
<p style="Normal" xid="513" props="text-align:left; dom-dir:ltr">    for (unsigned int i = 0; i &lt; tx.vin.size(); i++)</p>
<p style="Normal" xid="514">    {</p>
<p style="Normal" xid="515" props="text-align:left; dom-dir:ltr">        COutPoint outpoint = tx.vin[i].prevout;</p>
<p style="Normal" xid="516" props="text-align:left; dom-dir:ltr">        if (mapNextTx.count(outpoint))</p>
<p style="Normal" xid="517">        {</p>
<p style="Normal" xid="518" props="text-align:left; dom-dir:ltr">            // Disable replacement feature for now</p>
<p style="Normal" xid="519" props="text-align:left; dom-dir:ltr">            return false;</p>
<p style="Normal" xid="520"><c></c></p>
<p style="Normal" xid="521" props="text-align:left; dom-dir:ltr">            // Allow replacing with a newer version of the same transaction</p>
<p style="Normal" xid="522" props="text-align:left; dom-dir:ltr">            if (i != 0)</p>
<p style="Normal" xid="523" props="text-align:left; dom-dir:ltr">                return false;</p>
<p style="Normal" xid="524" props="text-align:left; dom-dir:ltr">            ptxOld = mapNextTx[outpoint].ptx;</p>
<p style="Normal" xid="525" props="text-align:left; dom-dir:ltr">            if (ptxOld-&gt;IsFinal())</p>
<p style="Normal" xid="526" props="text-align:left; dom-dir:ltr">                return false;</p>
<p style="Normal" xid="527" props="text-align:left; dom-dir:ltr">            if (!tx.IsNewerThan(*ptxOld))</p>
<p style="Normal" xid="528" props="text-align:left; dom-dir:ltr">                return false;</p>
<p style="Normal" xid="529" props="text-align:left; dom-dir:ltr">            for (unsigned int i = 0; i &lt; tx.vin.size(); i++)</p>
<p style="Normal" xid="530">            {</p>
<p style="Normal" xid="531" props="text-align:left; dom-dir:ltr">                COutPoint outpoint = tx.vin[i].prevout;</p>
<p style="Normal" xid="532" props="text-align:left; dom-dir:ltr">                if (!mapNextTx.count(outpoint) || mapNextTx[outpoint].ptx != ptxOld)</p>
<p style="Normal" xid="533" props="text-align:left; dom-dir:ltr">                    return false;</p>
<p style="Normal" xid="534">            }</p>
<p style="Normal" xid="535" props="text-align:left; dom-dir:ltr">            break;</p>
<p style="Normal" xid="536">        }</p>
<p style="Normal" xid="537">    }</p>
<p style="Normal" xid="538"><c></c></p>
<p style="Normal" xid="539" props="text-align:left; dom-dir:ltr">    if (fCheckInputs)</p>
<p style="Normal" xid="540">    {</p>
<p style="Normal" xid="541" props="text-align:left; dom-dir:ltr">        MapPrevTx mapInputs;</p>
<p style="Normal" xid="542" props="text-align:left; dom-dir:ltr">        map&lt;uint256, CTxIndex&gt; mapUnused;</p>
<p style="Normal" xid="543" props="text-align:left; dom-dir:ltr">        bool fInvalid = false;</p>
<p style="Normal" xid="544" props="text-align:left; dom-dir:ltr">        if (!tx.FetchInputs(txdb, mapUnused, false, false, mapInputs, fInvalid))</p>
<p style="Normal" xid="545">        {</p>
<p style="Normal" xid="546" props="text-align:left; dom-dir:ltr">            if (fInvalid)</p>
<p style="Normal" xid="547" props="text-align:left; dom-dir:ltr">                return error("CTxMemPool::accept() : FetchInputs found invalid tx %s", hash.ToString().substr(0,10).c_str());</p>
<p style="Normal" xid="548" props="text-align:left; dom-dir:ltr">            if (pfMissingInputs)</p>
<p style="Normal" xid="549" props="text-align:left; dom-dir:ltr">                *pfMissingInputs = true;</p>
<p style="Normal" xid="550" props="text-align:left; dom-dir:ltr">            return false;</p>
<p style="Normal" xid="551">        }</p>
<p style="Normal" xid="552"><c></c></p>
<p style="Normal" xid="553" props="text-align:left; dom-dir:ltr">        // Check for non-standard pay-to-script-hash in inputs</p>
<p style="Normal" xid="554" props="text-align:left; dom-dir:ltr">        if (!tx.AreInputsStandard(mapInputs) &amp;&amp; !fTestNet)</p>
<p style="Normal" xid="555" props="text-align:left; dom-dir:ltr">            return error("CTxMemPool::accept() : nonstandard transaction input");</p>
<p style="Normal" xid="556"><c></c></p>
<p style="Normal" xid="557" props="text-align:left; dom-dir:ltr">        // Note: if you modify this code to accept non-standard transactions, then</p>
<p style="Normal" xid="558" props="text-align:left; dom-dir:ltr">        // you should add code here to check that the transaction does a</p>
<p style="Normal" xid="559" props="text-align:left; dom-dir:ltr">        // reasonable number of ECDSA signature verifications.</p>
<p style="Normal" xid="560"><c></c></p>
<p style="Normal" xid="561" props="text-align:left; dom-dir:ltr">        int64 nFees = tx.GetValueIn(mapInputs)-tx.GetValueOut();</p>
<p style="Normal" xid="562" props="text-align:left; dom-dir:ltr">        unsigned int nSize = ::GetSerializeSize(tx, SER_NETWORK, PROTOCOL_VERSION);</p>
<p style="Normal" xid="563"><c></c></p>
<p style="Normal" xid="564" props="text-align:left; dom-dir:ltr">        // Don't accept it if it can't get into a block</p>
<p style="Normal" xid="565" props="text-align:left; dom-dir:ltr">        if (nFees &lt; tx.GetMinFee(1000, true, GMF_RELAY))</p>
<p style="Normal" xid="566" props="text-align:left; dom-dir:ltr">            return error("CTxMemPool::accept() : not enough fees");</p>
<p style="Normal" xid="567"><c></c></p>
<p style="Normal" xid="568" props="text-align:left; dom-dir:ltr">        // Continuously rate-limit free transactions</p>
<p style="Normal" xid="569" props="text-align:left; dom-dir:ltr">        // This mitigates 'penny-flooding' -- sending thousands of free transactions just to</p>
<p style="Normal" xid="570" props="text-align:left; dom-dir:ltr">        // be annoying or make other's transactions take longer to confirm.</p>
<p style="Normal" xid="571" props="text-align:left; dom-dir:ltr">        if (nFees &lt; MIN_RELAY_TX_FEE)</p>
<p style="Normal" xid="572">        {</p>
<p style="Normal" xid="573" props="text-align:left; dom-dir:ltr">            static CCriticalSection cs;</p>
<p style="Normal" xid="574" props="text-align:left; dom-dir:ltr">            static double dFreeCount;</p>
<p style="Normal" xid="575" props="text-align:left; dom-dir:ltr">            static int64 nLastTime;</p>
<p style="Normal" xid="576" props="text-align:left; dom-dir:ltr">            int64 nNow = GetTime();</p>
<p style="Normal" xid="577"><c></c></p>
<p style="Normal" xid="578">            {</p>
<p style="Normal" xid="579" props="text-align:left; dom-dir:ltr">                LOCK(cs);</p>
<p style="Normal" xid="580" props="text-align:left; dom-dir:ltr">                // Use an exponentially decaying ~10-minute window:</p>
<p style="Normal" xid="581" props="text-align:left; dom-dir:ltr">                dFreeCount *= pow(1.0 - 1.0/600.0, (double)(nNow - nLastTime));</p>
<p style="Normal" xid="582" props="text-align:left; dom-dir:ltr">                nLastTime = nNow;</p>
<p style="Normal" xid="583" props="text-align:left; dom-dir:ltr">                // -limitfreerelay unit is thousand-bytes-per-minute</p>
<p style="Normal" xid="584" props="text-align:left; dom-dir:ltr">                // At default rate it would take over a month to fill 1GB</p>
<p style="Normal" xid="585" props="text-align:left; dom-dir:ltr">                if (dFreeCount &gt; GetArg("-limitfreerelay", 15)*10*1000 &amp;&amp; !IsFromMe(tx))</p>
<p style="Normal" xid="586" props="text-align:left; dom-dir:ltr">                    return error("CTxMemPool::accept() : free transaction rejected by rate limiter");</p>
<p style="Normal" xid="587" props="text-align:left; dom-dir:ltr">                if (fDebug)</p>
<p style="Normal" xid="588" props="text-align:left; dom-dir:ltr">                    printf("Rate limit dFreeCount: %g =&gt; %g\n", dFreeCount, dFreeCount+nSize);</p>
<p style="Normal" xid="589" props="text-align:left; dom-dir:ltr">                dFreeCount += nSize;</p>
<p style="Normal" xid="590">            }</p>
<p style="Normal" xid="591">        }</p>
<p style="Normal" xid="592"><c></c></p>
<p style="Normal" xid="593" props="text-align:left; dom-dir:ltr">        // Check against previous transactions</p>
<p style="Normal" xid="594" props="text-align:left; dom-dir:ltr">        // This is done last to help prevent CPU exhaustion denial-of-service attacks.</p>
<p style="Normal" xid="595" props="text-align:left; dom-dir:ltr">        if (!tx.ConnectInputs(mapInputs, mapUnused, CDiskTxPos(1,1,1), pindexBest, false, false))</p>
<p style="Normal" xid="596">        {</p>
<p style="Normal" xid="597" props="text-align:left; dom-dir:ltr">            return error("CTxMemPool::accept() : ConnectInputs failed %s", hash.ToString().substr(0,10).c_str());</p>
<p style="Normal" xid="598">        }</p>
<p style="Normal" xid="599">    }</p>
<p style="Normal" xid="600"><c></c></p>
<p style="Normal" xid="601" props="text-align:left; dom-dir:ltr">    // Store transaction in memory</p>
<p style="Normal" xid="602">    {</p>
<p style="Normal" xid="603" props="text-align:left; dom-dir:ltr">        LOCK(cs);</p>
<p style="Normal" xid="604" props="text-align:left; dom-dir:ltr">        if (ptxOld)</p>
<p style="Normal" xid="605">        {</p>
<p style="Normal" xid="606" props="text-align:left; dom-dir:ltr">            printf("CTxMemPool::accept() : replacing tx %s with new version\n", ptxOld-&gt;GetHash().ToString().c_str());</p>
<p style="Normal" xid="607" props="text-align:left; dom-dir:ltr">            remove(*ptxOld);</p>
<p style="Normal" xid="608">        }</p>
<p style="Normal" xid="609" props="text-align:left; dom-dir:ltr">        addUnchecked(hash, tx);</p>
<p style="Normal" xid="610">    }</p>
<p style="Normal" xid="611"><c></c></p>
<p style="Normal" xid="612" props="text-align:left; dom-dir:ltr">    ///// are we sure this is ok when loading transactions or restoring block txes</p>
<p style="Normal" xid="613" props="text-align:left; dom-dir:ltr">    // If updated, erase old tx from wallet</p>
<p style="Normal" xid="614" props="text-align:left; dom-dir:ltr">    if (ptxOld)</p>
<p style="Normal" xid="615" props="text-align:left; dom-dir:ltr">        EraseFromWallets(ptxOld-&gt;GetHash());</p>
<p style="Normal" xid="616"><c></c></p>
<p style="Normal" xid="617" props="text-align:left; dom-dir:ltr">    printf("CTxMemPool::accept() : accepted %s (poolsz %u)\n",</p>
<p style="Normal" xid="618" props="text-align:left; dom-dir:ltr">           hash.ToString().substr(0,10).c_str(),</p>
<p style="Normal" xid="619" props="text-align:left; dom-dir:ltr">           mapTx.size());</p>
<p style="Normal" xid="620" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="621">}</p>
<p style="Normal" xid="622"><c></c></p>
<p style="Normal" xid="623" props="text-align:left; dom-dir:ltr">bool CTransaction::AcceptToMemoryPool(CTxDB&amp; txdb, bool fCheckInputs, bool* pfMissingInputs)</p>
<p style="Normal" xid="624">{</p>
<p style="Normal" xid="625" props="text-align:left; dom-dir:ltr">    return mempool.accept(txdb, *this, fCheckInputs, pfMissingInputs);</p>
<p style="Normal" xid="626">}</p>
<p style="Normal" xid="627"><c></c></p>
<p style="Normal" xid="628" props="text-align:left; dom-dir:ltr">bool CTxMemPool::addUnchecked(const uint256&amp; hash, CTransaction &amp;tx)</p>
<p style="Normal" xid="629">{</p>
<p style="Normal" xid="630" props="text-align:left; dom-dir:ltr">    // Add to memory pool without checking anything.  Don't call this directly,</p>
<p style="Normal" xid="631" props="text-align:left; dom-dir:ltr">    // call CTxMemPool::accept to properly check the transaction first.</p>
<p style="Normal" xid="632">    {</p>
<p style="Normal" xid="633" props="text-align:left; dom-dir:ltr">        mapTx[hash] = tx;</p>
<p style="Normal" xid="634" props="text-align:left; dom-dir:ltr">        for (unsigned int i = 0; i &lt; tx.vin.size(); i++)</p>
<p style="Normal" xid="635" props="text-align:left; dom-dir:ltr">            mapNextTx[tx.vin[i].prevout] = CInPoint(&amp;mapTx[hash], i);</p>
<p style="Normal" xid="636" props="text-align:left; dom-dir:ltr">        nTransactionsUpdated++;</p>
<p style="Normal" xid="637">    }</p>
<p style="Normal" xid="638" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="639">}</p>
<p style="Normal" xid="640"><c></c></p>
<p style="Normal" xid="641"><c></c></p>
<p style="Normal" xid="642" props="text-align:left; dom-dir:ltr">bool CTxMemPool::remove(CTransaction &amp;tx)</p>
<p style="Normal" xid="643">{</p>
<p style="Normal" xid="644" props="text-align:left; dom-dir:ltr">    // Remove transaction from memory pool</p>
<p style="Normal" xid="645">    {</p>
<p style="Normal" xid="646" props="text-align:left; dom-dir:ltr">        LOCK(cs);</p>
<p style="Normal" xid="647" props="text-align:left; dom-dir:ltr">        uint256 hash = tx.GetHash();</p>
<p style="Normal" xid="648" props="text-align:left; dom-dir:ltr">        if (mapTx.count(hash))</p>
<p style="Normal" xid="649">        {</p>
<p style="Normal" xid="650" props="text-align:left; dom-dir:ltr">            BOOST_FOREACH(const CTxIn&amp; txin, tx.vin)</p>
<p style="Normal" xid="651" props="text-align:left; dom-dir:ltr">                mapNextTx.erase(txin.prevout);</p>
<p style="Normal" xid="652" props="text-align:left; dom-dir:ltr">            mapTx.erase(hash);</p>
<p style="Normal" xid="653" props="text-align:left; dom-dir:ltr">            nTransactionsUpdated++;</p>
<p style="Normal" xid="654">        }</p>
<p style="Normal" xid="655">    }</p>
<p style="Normal" xid="656" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="657">}</p>
<p style="Normal" xid="658"><c></c></p>
<p style="Normal" xid="659" props="text-align:left; dom-dir:ltr">void CTxMemPool::queryHashes(std::vector&lt;uint256&gt;&amp; vtxid)</p>
<p style="Normal" xid="660">{</p>
<p style="Normal" xid="661" props="text-align:left; dom-dir:ltr">    vtxid.clear();</p>
<p style="Normal" xid="662"><c></c></p>
<p style="Normal" xid="663" props="text-align:left; dom-dir:ltr">    LOCK(cs);</p>
<p style="Normal" xid="664" props="text-align:left; dom-dir:ltr">    vtxid.reserve(mapTx.size());</p>
<p style="Normal" xid="665" props="text-align:left; dom-dir:ltr">    for (map&lt;uint256, CTransaction&gt;::iterator mi = mapTx.begin(); mi != mapTx.end(); ++mi)</p>
<p style="Normal" xid="666" props="text-align:left; dom-dir:ltr">        vtxid.push_back((*mi).first);</p>
<p style="Normal" xid="667">}</p>
<p style="Normal" xid="668"><c></c></p>
<p style="Normal" xid="669"><c></c></p>
<p style="Normal" xid="670"><c></c></p>
<p style="Normal" xid="671"><c></c></p>
<p style="Normal" xid="672" props="text-align:left; dom-dir:ltr">int CMerkleTx::GetDepthInMainChain(CBlockIndex* &amp;pindexRet) const</p>
<p style="Normal" xid="673">{</p>
<p style="Normal" xid="674" props="text-align:left; dom-dir:ltr">    if (hashBlock == 0 || nIndex == -1)</p>
<p style="Normal" xid="675" props="text-align:left; dom-dir:ltr">        return 0;</p>
<p style="Normal" xid="676"><c></c></p>
<p style="Normal" xid="677" props="text-align:left; dom-dir:ltr">    // Find the block it claims to be in</p>
<p style="Normal" xid="678" props="text-align:left; dom-dir:ltr">    map&lt;uint256, CBlockIndex*&gt;::iterator mi = mapBlockIndex.find(hashBlock);</p>
<p style="Normal" xid="679" props="text-align:left; dom-dir:ltr">    if (mi == mapBlockIndex.end())</p>
<p style="Normal" xid="680" props="text-align:left; dom-dir:ltr">        return 0;</p>
<p style="Normal" xid="681" props="text-align:left; dom-dir:ltr">    CBlockIndex* pindex = (*mi).second;</p>
<p style="Normal" xid="682" props="text-align:left; dom-dir:ltr">    if (!pindex || !pindex-&gt;IsInMainChain())</p>
<p style="Normal" xid="683" props="text-align:left; dom-dir:ltr">        return 0;</p>
<p style="Normal" xid="684"><c></c></p>
<p style="Normal" xid="685" props="text-align:left; dom-dir:ltr">    // Make sure the merkle branch connects to this block</p>
<p style="Normal" xid="686" props="text-align:left; dom-dir:ltr">    if (!fMerkleVerified)</p>
<p style="Normal" xid="687">    {</p>
<p style="Normal" xid="688" props="text-align:left; dom-dir:ltr">        if (CBlock::CheckMerkleBranch(GetHash(), vMerkleBranch, nIndex) != pindex-&gt;hashMerkleRoot)</p>
<p style="Normal" xid="689" props="text-align:left; dom-dir:ltr">            return 0;</p>
<p style="Normal" xid="690" props="text-align:left; dom-dir:ltr">        fMerkleVerified = true;</p>
<p style="Normal" xid="691">    }</p>
<p style="Normal" xid="692"><c></c></p>
<p style="Normal" xid="693" props="text-align:left; dom-dir:ltr">    pindexRet = pindex;</p>
<p style="Normal" xid="694" props="text-align:left; dom-dir:ltr">    return pindexBest-&gt;nHeight - pindex-&gt;nHeight + 1;</p>
<p style="Normal" xid="695">}</p>
<p style="Normal" xid="696"><c></c></p>
<p style="Normal" xid="697"><c></c></p>
<p style="Normal" xid="698" props="text-align:left; dom-dir:ltr">int CMerkleTx::GetBlocksToMaturity() const</p>
<p style="Normal" xid="699">{</p>
<p style="Normal" xid="700" props="text-align:left; dom-dir:ltr">    if (!IsCoinBase())</p>
<p style="Normal" xid="701" props="text-align:left; dom-dir:ltr">        return 0;</p>
<p style="Normal" xid="702" props="text-align:left; dom-dir:ltr">    return max(0, (COINBASE_MATURITY+10) - GetDepthInMainChain());</p>
<p style="Normal" xid="703">}</p>
<p style="Normal" xid="704"><c></c></p>
<p style="Normal" xid="705"><c></c></p>
<p style="Normal" xid="706" props="text-align:left; dom-dir:ltr">bool CMerkleTx::AcceptToMemoryPool(CTxDB&amp; txdb, bool fCheckInputs)</p>
<p style="Normal" xid="707">{</p>
<p style="Normal" xid="708" props="text-align:left; dom-dir:ltr">    if (fClient)</p>
<p style="Normal" xid="709">    {</p>
<p style="Normal" xid="710" props="text-align:left; dom-dir:ltr">        if (!IsInMainChain() &amp;&amp; !ClientConnectInputs())</p>
<p style="Normal" xid="711" props="text-align:left; dom-dir:ltr">            return false;</p>
<p style="Normal" xid="712" props="text-align:left; dom-dir:ltr">        return CTransaction::AcceptToMemoryPool(txdb, false);</p>
<p style="Normal" xid="713">    }</p>
<p style="Normal" xid="714" props="text-align:left; dom-dir:ltr">    else</p>
<p style="Normal" xid="715">    {</p>
<p style="Normal" xid="716" props="text-align:left; dom-dir:ltr">        return CTransaction::AcceptToMemoryPool(txdb, fCheckInputs);</p>
<p style="Normal" xid="717">    }</p>
<p style="Normal" xid="718">}</p>
<p style="Normal" xid="719"><c></c></p>
<p style="Normal" xid="720" props="text-align:left; dom-dir:ltr">bool CMerkleTx::AcceptToMemoryPool()</p>
<p style="Normal" xid="721">{</p>
<p style="Normal" xid="722" props="text-align:left; dom-dir:ltr">    CTxDB txdb("r");</p>
<p style="Normal" xid="723" props="text-align:left; dom-dir:ltr">    return AcceptToMemoryPool(txdb);</p>
<p style="Normal" xid="724">}</p>
<p style="Normal" xid="725"><c></c></p>
<p style="Normal" xid="726"><c></c></p>
<p style="Normal" xid="727"><c></c></p>
<p style="Normal" xid="728" props="text-align:left; dom-dir:ltr">bool CWalletTx::AcceptWalletTransaction(CTxDB&amp; txdb, bool fCheckInputs)</p>
<p style="Normal" xid="729">{</p>
<p style="Normal" xid="730"><c></c></p>
<p style="Normal" xid="731">    {</p>
<p style="Normal" xid="732" props="text-align:left; dom-dir:ltr">        LOCK(mempool.cs);</p>
<p style="Normal" xid="733" props="text-align:left; dom-dir:ltr">        // Add previous supporting transactions first</p>
<p style="Normal" xid="734" props="text-align:left; dom-dir:ltr">        BOOST_FOREACH(CMerkleTx&amp; tx, vtxPrev)</p>
<p style="Normal" xid="735">        {</p>
<p style="Normal" xid="736" props="text-align:left; dom-dir:ltr">            if (!tx.IsCoinBase())</p>
<p style="Normal" xid="737">            {</p>
<p style="Normal" xid="738" props="text-align:left; dom-dir:ltr">                uint256 hash = tx.GetHash();</p>
<p style="Normal" xid="739" props="text-align:left; dom-dir:ltr">                if (!mempool.exists(hash) &amp;&amp; !txdb.ContainsTx(hash))</p>
<p style="Normal" xid="740" props="text-align:left; dom-dir:ltr">                    tx.AcceptToMemoryPool(txdb, fCheckInputs);</p>
<p style="Normal" xid="741">            }</p>
<p style="Normal" xid="742">        }</p>
<p style="Normal" xid="743" props="text-align:left; dom-dir:ltr">        return AcceptToMemoryPool(txdb, fCheckInputs);</p>
<p style="Normal" xid="744">    }</p>
<p style="Normal" xid="745" props="text-align:left; dom-dir:ltr">    return false;</p>
<p style="Normal" xid="746">}</p>
<p style="Normal" xid="747"><c></c></p>
<p style="Normal" xid="748" props="text-align:left; dom-dir:ltr">bool CWalletTx::AcceptWalletTransaction()</p>
<p style="Normal" xid="749">{</p>
<p style="Normal" xid="750" props="text-align:left; dom-dir:ltr">    CTxDB txdb("r");</p>
<p style="Normal" xid="751" props="text-align:left; dom-dir:ltr">    return AcceptWalletTransaction(txdb);</p>
<p style="Normal" xid="752">}</p>
<p style="Normal" xid="753"><c></c></p>
<p style="Normal" xid="754" props="text-align:left; dom-dir:ltr">int CTxIndex::GetDepthInMainChain() const</p>
<p style="Normal" xid="755">{</p>
<p style="Normal" xid="756" props="text-align:left; dom-dir:ltr">    // Read block header</p>
<p style="Normal" xid="757" props="text-align:left; dom-dir:ltr">    CBlock block;</p>
<p style="Normal" xid="758" props="text-align:left; dom-dir:ltr">    if (!block.ReadFromDisk(pos.nFile, pos.nBlockPos, false))</p>
<p style="Normal" xid="759" props="text-align:left; dom-dir:ltr">        return 0;</p>
<p style="Normal" xid="760" props="text-align:left; dom-dir:ltr">    // Find the block in the index</p>
<p style="Normal" xid="761" props="text-align:left; dom-dir:ltr">    map&lt;uint256, CBlockIndex*&gt;::iterator mi = mapBlockIndex.find(block.GetHash());</p>
<p style="Normal" xid="762" props="text-align:left; dom-dir:ltr">    if (mi == mapBlockIndex.end())</p>
<p style="Normal" xid="763" props="text-align:left; dom-dir:ltr">        return 0;</p>
<p style="Normal" xid="764" props="text-align:left; dom-dir:ltr">    CBlockIndex* pindex = (*mi).second;</p>
<p style="Normal" xid="765" props="text-align:left; dom-dir:ltr">    if (!pindex || !pindex-&gt;IsInMainChain())</p>
<p style="Normal" xid="766" props="text-align:left; dom-dir:ltr">        return 0;</p>
<p style="Normal" xid="767" props="text-align:left; dom-dir:ltr">    return 1 + nBestHeight - pindex-&gt;nHeight;</p>
<p style="Normal" xid="768">}</p>
<p style="Normal" xid="769"><c></c></p>
<p style="Normal" xid="770" props="text-align:left; dom-dir:ltr">// Return transaction in tx, and if it was found inside a block, its hash is placed in hashBlock</p>
<p style="Normal" xid="771" props="text-align:left; dom-dir:ltr">bool GetTransaction(const uint256 &amp;hash, CTransaction &amp;tx, uint256 &amp;hashBlock)</p>
<p style="Normal" xid="772">{</p>
<p style="Normal" xid="773">    {</p>
<p style="Normal" xid="774" props="text-align:left; dom-dir:ltr">        LOCK(cs_main);</p>
<p style="Normal" xid="775">        {</p>
<p style="Normal" xid="776" props="text-align:left; dom-dir:ltr">            LOCK(mempool.cs);</p>
<p style="Normal" xid="777" props="text-align:left; dom-dir:ltr">            if (mempool.exists(hash))</p>
<p style="Normal" xid="778">            {</p>
<p style="Normal" xid="779" props="text-align:left; dom-dir:ltr">                tx = mempool.lookup(hash);</p>
<p style="Normal" xid="780" props="text-align:left; dom-dir:ltr">                return true;</p>
<p style="Normal" xid="781">            }</p>
<p style="Normal" xid="782">        }</p>
<p style="Normal" xid="783" props="text-align:left; dom-dir:ltr">        CTxDB txdb("r");</p>
<p style="Normal" xid="784" props="text-align:left; dom-dir:ltr">        CTxIndex txindex;</p>
<p style="Normal" xid="785" props="text-align:left; dom-dir:ltr">        if (tx.ReadFromDisk(txdb, COutPoint(hash, 0), txindex))</p>
<p style="Normal" xid="786">        {</p>
<p style="Normal" xid="787" props="text-align:left; dom-dir:ltr">            CBlock block;</p>
<p style="Normal" xid="788" props="text-align:left; dom-dir:ltr">            if (block.ReadFromDisk(txindex.pos.nFile, txindex.pos.nBlockPos, false))</p>
<p style="Normal" xid="789" props="text-align:left; dom-dir:ltr">                hashBlock = block.GetHash();</p>
<p style="Normal" xid="790" props="text-align:left; dom-dir:ltr">            return true;</p>
<p style="Normal" xid="791">        }</p>
<p style="Normal" xid="792">    }</p>
<p style="Normal" xid="793" props="text-align:left; dom-dir:ltr">    return false;</p>
<p style="Normal" xid="794">}</p>
<p style="Normal" xid="795"><c></c></p>
<p style="Normal" xid="796"><c></c></p>
<p style="Normal" xid="797"><c></c></p>
<p style="Normal" xid="798"><c></c></p>
<p style="Normal" xid="799"><c></c></p>
<p style="Normal" xid="800"><c></c></p>
<p style="Normal" xid="801"><c></c></p>
<p style="Normal" xid="802"><c></c></p>
<p style="Normal" xid="803">//////////////////////////////////////////////////////////////////////////////</p>
<p style="Normal" xid="804">//</p>
<p style="Normal" xid="805" props="text-align:left; dom-dir:ltr">// CBlock and CBlockIndex</p>
<p style="Normal" xid="806">//</p>
<p style="Normal" xid="807"><c></c></p>
<p style="Normal" xid="808" props="text-align:left; dom-dir:ltr">bool CBlock::ReadFromDisk(const CBlockIndex* pindex, bool fReadTransactions)</p>
<p style="Normal" xid="809">{</p>
<p style="Normal" xid="810" props="text-align:left; dom-dir:ltr">    if (!fReadTransactions)</p>
<p style="Normal" xid="811">    {</p>
<p style="Normal" xid="812" props="text-align:left; dom-dir:ltr">        *this = pindex-&gt;GetBlockHeader();</p>
<p style="Normal" xid="813" props="text-align:left; dom-dir:ltr">        return true;</p>
<p style="Normal" xid="814">    }</p>
<p style="Normal" xid="815" props="text-align:left; dom-dir:ltr">    if (!ReadFromDisk(pindex-&gt;nFile, pindex-&gt;nBlockPos, fReadTransactions))</p>
<p style="Normal" xid="816" props="text-align:left; dom-dir:ltr">        return false;</p>
<p style="Normal" xid="817" props="text-align:left; dom-dir:ltr">    if (GetHash() != pindex-&gt;GetBlockHash())</p>
<p style="Normal" xid="818" props="text-align:left; dom-dir:ltr">        return error("CBlock::ReadFromDisk() : GetHash() doesn't match index");</p>
<p style="Normal" xid="819" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="820">}</p>
<p style="Normal" xid="821"><c></c></p>
<p style="Normal" xid="822" props="text-align:left; dom-dir:ltr">uint256 static GetOrphanRoot(const CBlock* pblock)</p>
<p style="Normal" xid="823">{</p>
<p style="Normal" xid="824" props="text-align:left; dom-dir:ltr">    // Work back to the first block in the orphan chain</p>
<p style="Normal" xid="825" props="text-align:left; dom-dir:ltr">    while (mapOrphanBlocks.count(pblock-&gt;hashPrevBlock))</p>
<p style="Normal" xid="826" props="text-align:left; dom-dir:ltr">        pblock = mapOrphanBlocks[pblock-&gt;hashPrevBlock];</p>
<p style="Normal" xid="827" props="text-align:left; dom-dir:ltr">    return pblock-&gt;GetHash();</p>
<p style="Normal" xid="828">}</p>
<p style="Normal" xid="829"><c></c></p>
<p style="Normal" xid="830" props="text-align:left; dom-dir:ltr">int64 static GetBlockValue(int nHeight, int64 nFees)</p>
<p style="Normal" xid="831">{</p>
<p style="Normal" xid="832" props="text-align:left; dom-dir:ltr">    int64 nSubsidy = 10000 * COIN; // 10 000 Coins each block</p>
<p style="Normal" xid="833"><c></c></p>
<p style="Normal" xid="834"><c></c></p>
<p style="Normal" xid="835" props="text-align:left; dom-dir:ltr">    if(nHeight &lt; 17280) // no block reward within the first 3 days</p>
<p style="Normal" xid="836" props="text-align:left; dom-dir:ltr">        nSubsidy = 0;</p>
<p style="Normal" xid="837" props="text-align:left; dom-dir:ltr">    if(nHeight &gt; 10519200) // no block reward after 5 years</p>
<p style="Normal" xid="838" props="text-align:left; dom-dir:ltr">        nSubsidy = 0;</p>
<p style="Normal" xid="839"><c></c></p>
<p style="Normal" xid="840" props="text-align:left; dom-dir:ltr">    return nSubsidy + nFees;</p>
<p style="Normal" xid="841">}</p>
<p style="Normal" xid="842"><c></c></p>
<p style="Normal" xid="843" props="text-align:left; dom-dir:ltr">static const int64 nTargetTimespan = 0.25 * 24 * 60 * 60; // FlightCoin: 0.25 days</p>
<p style="Normal" xid="844" props="text-align:left; dom-dir:ltr">static const int64 nTargetSpacing = 500; // FlightCoin: 15 seconds</p>
<p style="Normal" xid="845" props="text-align:left; dom-dir:ltr">static const int64 nInterval = nTargetTimespan / nTargetSpacing;</p>
<p style="Normal" xid="846"><c></c></p>
<p style="Normal" xid="847" props="text-align:left; dom-dir:ltr">// Thanks: Balthazar for suggesting the following fix</p>
<p style="Normal" xid="848" props="text-align:left; dom-dir:ltr">// https://bitcointalk.org/index.php?topic=182430.msg1904506#msg1904506</p>
<p style="Normal" xid="849" props="text-align:left; dom-dir:ltr">static const int64 nReTargetHistoryFact = 4; // look at 4 times the retarget</p>
<p style="Normal" xid="850" props="text-align:left; dom-dir:ltr">                                             // interval into the block history</p>
<p style="Normal" xid="851"><c></c></p>
<p style="Normal" xid="852">//</p>
<p style="Normal" xid="853" props="text-align:left; dom-dir:ltr">// minimum amount of work that could possibly be required nTime after</p>
<p style="Normal" xid="854" props="text-align:left; dom-dir:ltr">// minimum work required was nBase</p>
<p style="Normal" xid="855">//</p>
<p style="Normal" xid="856" props="text-align:left; dom-dir:ltr">unsigned int ComputeMinWork(unsigned int nBase, int64 nTime)</p>
<p style="Normal" xid="857">{</p>
<p style="Normal" xid="858" props="text-align:left; dom-dir:ltr">    // Testnet has min-difficulty blocks</p>
<p style="Normal" xid="859" props="text-align:left; dom-dir:ltr">    // after nTargetSpacing*2 time between blocks:</p>
<p style="Normal" xid="860" props="text-align:left; dom-dir:ltr">    if (fTestNet &amp;&amp; nTime &gt; nTargetSpacing*2)</p>
<p style="Normal" xid="861" props="text-align:left; dom-dir:ltr">        return bnProofOfWorkLimit.GetCompact();</p>
<p style="Normal" xid="862"><c></c></p>
<p style="Normal" xid="863" props="text-align:left; dom-dir:ltr">    CBigNum bnResult;</p>
<p style="Normal" xid="864" props="text-align:left; dom-dir:ltr">    bnResult.SetCompact(nBase);</p>
<p style="Normal" xid="865" props="text-align:left; dom-dir:ltr">    while (nTime &gt; 0 &amp;&amp; bnResult &lt; bnProofOfWorkLimit)</p>
<p style="Normal" xid="866">    {</p>
<p style="Normal" xid="867" props="text-align:left; dom-dir:ltr">        // Maximum 400% adjustment...</p>
<p style="Normal" xid="868" props="text-align:left; dom-dir:ltr">        bnResult *= 4;</p>
<p style="Normal" xid="869" props="text-align:left; dom-dir:ltr">        // ... in best-case exactly 4-times-normal target time</p>
<p style="Normal" xid="870" props="text-align:left; dom-dir:ltr">        nTime -= nTargetTimespan*4;</p>
<p style="Normal" xid="871">    }</p>
<p style="Normal" xid="872" props="text-align:left; dom-dir:ltr">    if (bnResult &gt; bnProofOfWorkLimit)</p>
<p style="Normal" xid="873" props="text-align:left; dom-dir:ltr">        bnResult = bnProofOfWorkLimit;</p>
<p style="Normal" xid="874" props="text-align:left; dom-dir:ltr">    return bnResult.GetCompact();</p>
<p style="Normal" xid="875">}</p>
<p style="Normal" xid="876"><c></c></p>
<p style="Normal" xid="877" props="text-align:left; dom-dir:ltr">unsigned int static GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlock *pblock)</p>
<p style="Normal" xid="878">{</p>
<p style="Normal" xid="879" props="text-align:left; dom-dir:ltr">    unsigned int nProofOfWorkLimit = bnProofOfWorkLimit.GetCompact();</p>
<p style="Normal" xid="880"><c></c></p>
<p style="Normal" xid="881" props="text-align:left; dom-dir:ltr">    // Genesis block</p>
<p style="Normal" xid="882" props="text-align:left; dom-dir:ltr">    if (pindexLast == NULL)</p>
<p style="Normal" xid="883" props="text-align:left; dom-dir:ltr">        return nProofOfWorkLimit;</p>
<p style="Normal" xid="884"><c></c></p>
<p style="Normal" xid="885" props="text-align:left; dom-dir:ltr">    // Only change once per interval</p>
<p style="Normal" xid="886" props="text-align:left; dom-dir:ltr">    if ((pindexLast-&gt;nHeight+1) % nInterval != 0)</p>
<p style="Normal" xid="887">    {</p>
<p style="Normal" xid="888" props="text-align:left; dom-dir:ltr">        // Special difficulty rule for testnet:</p>
<p style="Normal" xid="889" props="text-align:left; dom-dir:ltr">        if (fTestNet)</p>
<p style="Normal" xid="890">        {</p>
<p style="Normal" xid="891" props="text-align:left; dom-dir:ltr">            // If the new block's timestamp is more than 2* 10 minutes</p>
<p style="Normal" xid="892" props="text-align:left; dom-dir:ltr">            // then allow mining of a min-difficulty block.</p>
<p style="Normal" xid="893" props="text-align:left; dom-dir:ltr">            if (pblock-&gt;nTime &gt; pindexLast-&gt;nTime + nTargetSpacing*2)</p>
<p style="Normal" xid="894" props="text-align:left; dom-dir:ltr">                return nProofOfWorkLimit;</p>
<p style="Normal" xid="895" props="text-align:left; dom-dir:ltr">            else</p>
<p style="Normal" xid="896">            {</p>
<p style="Normal" xid="897" props="text-align:left; dom-dir:ltr">                // Return the last non-special-min-difficulty-rules-block</p>
<p style="Normal" xid="898" props="text-align:left; dom-dir:ltr">                const CBlockIndex* pindex = pindexLast;</p>
<p style="Normal" xid="899" props="text-align:left; dom-dir:ltr">                while (pindex-&gt;pprev &amp;&amp; pindex-&gt;nHeight % nInterval != 0 &amp;&amp; pindex-&gt;nBits == nProofOfWorkLimit)</p>
<p style="Normal" xid="900" props="text-align:left; dom-dir:ltr">                    pindex = pindex-&gt;pprev;</p>
<p style="Normal" xid="901" props="text-align:left; dom-dir:ltr">                return pindex-&gt;nBits;</p>
<p style="Normal" xid="902">            }</p>
<p style="Normal" xid="903">        }</p>
<p style="Normal" xid="904"><c></c></p>
<p style="Normal" xid="905" props="text-align:left; dom-dir:ltr">        return pindexLast-&gt;nBits;</p>
<p style="Normal" xid="906">    }</p>
<p style="Normal" xid="907"><c></c></p>
<p style="Normal" xid="908" props="text-align:left; dom-dir:ltr">    // Litecoin: This fixes an issue where a 51% attack can change difficulty at will.</p>
<p style="Normal" xid="909" props="text-align:left; dom-dir:ltr">    // Go back the full period unless it's the first retarget after genesis. Code courtesy of Art Forz</p>
<p style="Normal" xid="910" props="text-align:left; dom-dir:ltr">    int blockstogoback = nInterval-1;</p>
<p style="Normal" xid="911" props="text-align:left; dom-dir:ltr">    if ((pindexLast-&gt;nHeight+1) != nInterval)</p>
<p style="Normal" xid="912" props="text-align:left; dom-dir:ltr">        blockstogoback = nInterval;</p>
<p style="Normal" xid="913" props="text-align:left; dom-dir:ltr">    if (pindexLast-&gt;nHeight &gt; COINFIX1_BLOCK) {</p>
<p style="Normal" xid="914" props="text-align:left; dom-dir:ltr">        blockstogoback = nReTargetHistoryFact * nInterval;</p>
<p style="Normal" xid="915">    }</p>
<p style="Normal" xid="916"><c></c></p>
<p style="Normal" xid="917" props="text-align:left; dom-dir:ltr">    // Go back by what we want to be nReTargetHistoryFact*nInterval blocks</p>
<p style="Normal" xid="918" props="text-align:left; dom-dir:ltr">    const CBlockIndex* pindexFirst = pindexLast;</p>
<p style="Normal" xid="919" props="text-align:left; dom-dir:ltr">    for (int i = 0; pindexFirst &amp;&amp; i &lt; blockstogoback; i++)</p>
<p style="Normal" xid="920" props="text-align:left; dom-dir:ltr">        pindexFirst = pindexFirst-&gt;pprev;</p>
<p style="Normal" xid="921" props="text-align:left; dom-dir:ltr">    assert(pindexFirst);</p>
<p style="Normal" xid="922"><c></c></p>
<p style="Normal" xid="923" props="text-align:left; dom-dir:ltr">    // Limit adjustment step</p>
<p style="Normal" xid="924" props="text-align:left; dom-dir:ltr">    int64 nActualTimespan = 0;</p>
<p style="Normal" xid="925" props="text-align:left; dom-dir:ltr">    if (pindexLast-&gt;nHeight &gt; COINFIX1_BLOCK)</p>
<p style="Normal" xid="926" props="text-align:left; dom-dir:ltr">        // obtain average actual timespan</p>
<p style="Normal" xid="927" props="text-align:left; dom-dir:ltr">        nActualTimespan = (pindexLast-&gt;GetBlockTime() - pindexFirst-&gt;GetBlockTime())/nReTargetHistoryFact;</p>
<p style="Normal" xid="928" props="text-align:left; dom-dir:ltr">    else</p>
<p style="Normal" xid="929" props="text-align:left; dom-dir:ltr">        nActualTimespan = pindexLast-&gt;GetBlockTime() - pindexFirst-&gt;GetBlockTime();</p>
<p style="Normal" xid="930" props="text-align:left; dom-dir:ltr">    printf("  nActualTimespan = %"PRI64d"  before bounds\n", nActualTimespan);</p>
<p style="Normal" xid="931" props="text-align:left; dom-dir:ltr">    if (nActualTimespan &lt; nTargetTimespan/4)</p>
<p style="Normal" xid="932" props="text-align:left; dom-dir:ltr">        nActualTimespan = nTargetTimespan/4;</p>
<p style="Normal" xid="933" props="text-align:left; dom-dir:ltr">    if (nActualTimespan &gt; nTargetTimespan*4)</p>
<p style="Normal" xid="934" props="text-align:left; dom-dir:ltr">        nActualTimespan = nTargetTimespan*4;</p>
<p style="Normal" xid="935"><c></c></p>
<p style="Normal" xid="936" props="text-align:left; dom-dir:ltr">    // Retarget</p>
<p style="Normal" xid="937" props="text-align:left; dom-dir:ltr">    CBigNum bnNew;</p>
<p style="Normal" xid="938" props="text-align:left; dom-dir:ltr">    bnNew.SetCompact(pindexLast-&gt;nBits);</p>
<p style="Normal" xid="939" props="text-align:left; dom-dir:ltr">    bnNew *= nActualTimespan;</p>
<p style="Normal" xid="940" props="text-align:left; dom-dir:ltr">    bnNew /= nTargetTimespan;</p>
<p style="Normal" xid="941"><c></c></p>
<p style="Normal" xid="942" props="text-align:left; dom-dir:ltr">    if (bnNew &gt; bnProofOfWorkLimit)</p>
<p style="Normal" xid="943" props="text-align:left; dom-dir:ltr">        bnNew = bnProofOfWorkLimit;</p>
<p style="Normal" xid="944"><c></c></p>
<p style="Normal" xid="945" props="text-align:left; dom-dir:ltr">    /// debug print</p>
<p style="Normal" xid="946" props="text-align:left; dom-dir:ltr">    printf("GetNextWorkRequired RETARGET\n");</p>
<p style="Normal" xid="947" props="text-align:left; dom-dir:ltr">    printf("nTargetTimespan = %"PRI64d"    nActualTimespan = %"PRI64d"\n", nTargetTimespan, nActualTimespan);</p>
<p style="Normal" xid="948" props="text-align:left; dom-dir:ltr">    printf("Before: %08x  %s\n", pindexLast-&gt;nBits, CBigNum().SetCompact(pindexLast-&gt;nBits).getuint256().ToString().c_str());</p>
<p style="Normal" xid="949" props="text-align:left; dom-dir:ltr">    printf("After:  %08x  %s\n", bnNew.GetCompact(), bnNew.getuint256().ToString().c_str());</p>
<p style="Normal" xid="950"><c></c></p>
<p style="Normal" xid="951" props="text-align:left; dom-dir:ltr">    return bnNew.GetCompact();</p>
<p style="Normal" xid="952">}</p>
<p style="Normal" xid="953"><c></c></p>
<p style="Normal" xid="954" props="text-align:left; dom-dir:ltr">bool CheckProofOfWork(uint256 hash, unsigned int nBits)</p>
<p style="Normal" xid="955">{</p>
<p style="Normal" xid="956" props="text-align:left; dom-dir:ltr">    CBigNum bnTarget;</p>
<p style="Normal" xid="957" props="text-align:left; dom-dir:ltr">    bnTarget.SetCompact(nBits);</p>
<p style="Normal" xid="958"><c></c></p>
<p style="Normal" xid="959" props="text-align:left; dom-dir:ltr">    // Check range</p>
<p style="Normal" xid="960" props="text-align:left; dom-dir:ltr">    if (bnTarget &lt;= 0 || bnTarget &gt; bnProofOfWorkLimit)</p>
<p style="Normal" xid="961" props="text-align:left; dom-dir:ltr">        return error("CheckProofOfWork() : nBits below minimum work");</p>
<p style="Normal" xid="962"><c></c></p>
<p style="Normal" xid="963" props="text-align:left; dom-dir:ltr">    // Check proof of work matches claimed amount</p>
<p style="Normal" xid="964" props="text-align:left; dom-dir:ltr">    if (hash &gt; bnTarget.getuint256())</p>
<p style="Normal" xid="965" props="text-align:left; dom-dir:ltr">        return error("CheckProofOfWork() : hash doesn't match nBits");</p>
<p style="Normal" xid="966"><c></c></p>
<p style="Normal" xid="967" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="968">}</p>
<p style="Normal" xid="969"><c></c></p>
<p style="Normal" xid="970" props="text-align:left; dom-dir:ltr">// Return maximum amount of blocks that other nodes claim to have</p>
<p style="Normal" xid="971" props="text-align:left; dom-dir:ltr">int GetNumBlocksOfPeers()</p>
<p style="Normal" xid="972">{</p>
<p style="Normal" xid="973" props="text-align:left; dom-dir:ltr">    return std::max(cPeerBlockCounts.median(), Checkpoints::GetTotalBlocksEstimate());</p>
<p style="Normal" xid="974">}</p>
<p style="Normal" xid="975"><c></c></p>
<p style="Normal" xid="976" props="text-align:left; dom-dir:ltr">bool IsInitialBlockDownload()</p>
<p style="Normal" xid="977">{</p>
<p style="Normal" xid="978" props="text-align:left; dom-dir:ltr">    if (pindexBest == NULL || nBestHeight &lt; Checkpoints::GetTotalBlocksEstimate())</p>
<p style="Normal" xid="979" props="text-align:left; dom-dir:ltr">        return true;</p>
<p style="Normal" xid="980" props="text-align:left; dom-dir:ltr">    static int64 nLastUpdate;</p>
<p style="Normal" xid="981" props="text-align:left; dom-dir:ltr">    static CBlockIndex* pindexLastBest;</p>
<p style="Normal" xid="982" props="text-align:left; dom-dir:ltr">    if (pindexBest != pindexLastBest)</p>
<p style="Normal" xid="983">    {</p>
<p style="Normal" xid="984" props="text-align:left; dom-dir:ltr">        pindexLastBest = pindexBest;</p>
<p style="Normal" xid="985" props="text-align:left; dom-dir:ltr">        nLastUpdate = GetTime();</p>
<p style="Normal" xid="986">    }</p>
<p style="Normal" xid="987" props="text-align:left; dom-dir:ltr">    return (GetTime() - nLastUpdate &lt; 10 &amp;&amp;</p>
<p style="Normal" xid="988" props="text-align:left; dom-dir:ltr">            pindexBest-&gt;GetBlockTime() &lt; GetTime() - 24 * 60 * 60);</p>
<p style="Normal" xid="989">}</p>
<p style="Normal" xid="990"><c></c></p>
<p style="Normal" xid="991" props="text-align:left; dom-dir:ltr">void static InvalidChainFound(CBlockIndex* pindexNew)</p>
<p style="Normal" xid="992">{</p>
<p style="Normal" xid="993" props="text-align:left; dom-dir:ltr">    if (pindexNew-&gt;bnChainWork &gt; bnBestInvalidWork)</p>
<p style="Normal" xid="994">    {</p>
<p style="Normal" xid="995" props="text-align:left; dom-dir:ltr">        bnBestInvalidWork = pindexNew-&gt;bnChainWork;</p>
<p style="Normal" xid="996" props="text-align:left; dom-dir:ltr">        CTxDB().WriteBestInvalidWork(bnBestInvalidWork);</p>
<p style="Normal" xid="997" props="text-align:left; dom-dir:ltr">        uiInterface.NotifyBlocksChanged();</p>
<p style="Normal" xid="998">    }</p>
<p style="Normal" xid="999" props="text-align:left; dom-dir:ltr">    printf("InvalidChainFound: invalid block=%s  height=%d  work=%s  date=%s\n",</p>
<p style="Normal" xid="1000" props="text-align:left; dom-dir:ltr">      pindexNew-&gt;GetBlockHash().ToString().substr(0,20).c_str(), pindexNew-&gt;nHeight,</p>
<p style="Normal" xid="1001" props="text-align:left; dom-dir:ltr">      pindexNew-&gt;bnChainWork.ToString().c_str(), DateTimeStrFormat("%x %H:%M:%S",</p>
<p style="Normal" xid="1002" props="text-align:left; dom-dir:ltr">      pindexNew-&gt;GetBlockTime()).c_str());</p>
<p style="Normal" xid="1003" props="text-align:left; dom-dir:ltr">    printf("InvalidChainFound:  current best=%s  height=%d  work=%s  date=%s\n",</p>
<p style="Normal" xid="1004" props="text-align:left; dom-dir:ltr">      hashBestChain.ToString().substr(0,20).c_str(), nBestHeight, bnBestChainWork.ToString().c_str(),</p>
<p style="Normal" xid="1005" props="text-align:left; dom-dir:ltr">      DateTimeStrFormat("%x %H:%M:%S", pindexBest-&gt;GetBlockTime()).c_str());</p>
<p style="Normal" xid="1006" props="text-align:left; dom-dir:ltr">    if (pindexBest &amp;&amp; bnBestInvalidWork &gt; bnBestChainWork + pindexBest-&gt;GetBlockWork() * 6)</p>
<p style="Normal" xid="1007" props="text-align:left; dom-dir:ltr">        printf("InvalidChainFound: WARNING: Displayed transactions may not be correct!  You may need to upgrade, or other nodes may need to upgrade.\n");</p>
<p style="Normal" xid="1008">}</p>
<p style="Normal" xid="1009"><c></c></p>
<p style="Normal" xid="1010" props="text-align:left; dom-dir:ltr">void CBlock::UpdateTime(const CBlockIndex* pindexPrev)</p>
<p style="Normal" xid="1011">{</p>
<p style="Normal" xid="1012" props="text-align:left; dom-dir:ltr">    nTime = max(pindexPrev-&gt;GetMedianTimePast()+1, GetAdjustedTime());</p>
<p style="Normal" xid="1013"><c></c></p>
<p style="Normal" xid="1014" props="text-align:left; dom-dir:ltr">    // Updating time can change work required on testnet:</p>
<p style="Normal" xid="1015" props="text-align:left; dom-dir:ltr">    if (fTestNet)</p>
<p style="Normal" xid="1016" props="text-align:left; dom-dir:ltr">        nBits = GetNextWorkRequired(pindexPrev, this);</p>
<p style="Normal" xid="1017">}</p>
<p style="Normal" xid="1018"><c></c></p>
<p style="Normal" xid="1019"><c></c></p>
<p style="Normal" xid="1020"><c></c></p>
<p style="Normal" xid="1021"><c></c></p>
<p style="Normal" xid="1022"><c></c></p>
<p style="Normal" xid="1023"><c></c></p>
<p style="Normal" xid="1024"><c></c></p>
<p style="Normal" xid="1025"><c></c></p>
<p style="Normal" xid="1026"><c></c></p>
<p style="Normal" xid="1027"><c></c></p>
<p style="Normal" xid="1028"><c></c></p>
<p style="Normal" xid="1029" props="text-align:left; dom-dir:ltr">bool CTransaction::DisconnectInputs(CTxDB&amp; txdb)</p>
<p style="Normal" xid="1030">{</p>
<p style="Normal" xid="1031" props="text-align:left; dom-dir:ltr">    // Relinquish previous transactions' spent pointers</p>
<p style="Normal" xid="1032" props="text-align:left; dom-dir:ltr">    if (!IsCoinBase())</p>
<p style="Normal" xid="1033">    {</p>
<p style="Normal" xid="1034" props="text-align:left; dom-dir:ltr">        BOOST_FOREACH(const CTxIn&amp; txin, vin)</p>
<p style="Normal" xid="1035">        {</p>
<p style="Normal" xid="1036" props="text-align:left; dom-dir:ltr">            COutPoint prevout = txin.prevout;</p>
<p style="Normal" xid="1037"><c></c></p>
<p style="Normal" xid="1038" props="text-align:left; dom-dir:ltr">            // Get prev txindex from disk</p>
<p style="Normal" xid="1039" props="text-align:left; dom-dir:ltr">            CTxIndex txindex;</p>
<p style="Normal" xid="1040" props="text-align:left; dom-dir:ltr">            if (!txdb.ReadTxIndex(prevout.hash, txindex))</p>
<p style="Normal" xid="1041" props="text-align:left; dom-dir:ltr">                return error("DisconnectInputs() : ReadTxIndex failed");</p>
<p style="Normal" xid="1042"><c></c></p>
<p style="Normal" xid="1043" props="text-align:left; dom-dir:ltr">            if (prevout.n &gt;= txindex.vSpent.size())</p>
<p style="Normal" xid="1044" props="text-align:left; dom-dir:ltr">                return error("DisconnectInputs() : prevout.n out of range");</p>
<p style="Normal" xid="1045"><c></c></p>
<p style="Normal" xid="1046" props="text-align:left; dom-dir:ltr">            // Mark outpoint as not spent</p>
<p style="Normal" xid="1047" props="text-align:left; dom-dir:ltr">            txindex.vSpent[prevout.n].SetNull();</p>
<p style="Normal" xid="1048"><c></c></p>
<p style="Normal" xid="1049" props="text-align:left; dom-dir:ltr">            // Write back</p>
<p style="Normal" xid="1050" props="text-align:left; dom-dir:ltr">            if (!txdb.UpdateTxIndex(prevout.hash, txindex))</p>
<p style="Normal" xid="1051" props="text-align:left; dom-dir:ltr">                return error("DisconnectInputs() : UpdateTxIndex failed");</p>
<p style="Normal" xid="1052">        }</p>
<p style="Normal" xid="1053">    }</p>
<p style="Normal" xid="1054"><c></c></p>
<p style="Normal" xid="1055" props="text-align:left; dom-dir:ltr">    // Remove transaction from index</p>
<p style="Normal" xid="1056" props="text-align:left; dom-dir:ltr">    // This can fail if a duplicate of this transaction was in a chain that got</p>
<p style="Normal" xid="1057" props="text-align:left; dom-dir:ltr">    // reorganized away. This is only possible if this transaction was completely</p>
<p style="Normal" xid="1058" props="text-align:left; dom-dir:ltr">    // spent, so erasing it would be a no-op anway.</p>
<p style="Normal" xid="1059" props="text-align:left; dom-dir:ltr">    txdb.EraseTxIndex(*this);</p>
<p style="Normal" xid="1060"><c></c></p>
<p style="Normal" xid="1061" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="1062">}</p>
<p style="Normal" xid="1063"><c></c></p>
<p style="Normal" xid="1064"><c></c></p>
<p style="Normal" xid="1065" props="text-align:left; dom-dir:ltr">bool CTransaction::FetchInputs(CTxDB&amp; txdb, const map&lt;uint256, CTxIndex&gt;&amp; mapTestPool,</p>
<p style="Normal" xid="1066" props="text-align:left; dom-dir:ltr">                               bool fBlock, bool fMiner, MapPrevTx&amp; inputsRet, bool&amp; fInvalid)</p>
<p style="Normal" xid="1067">{</p>
<p style="Normal" xid="1068" props="text-align:left; dom-dir:ltr">    // FetchInputs can return false either because we just haven't seen some inputs</p>
<p style="Normal" xid="1069" props="text-align:left; dom-dir:ltr">    // (in which case the transaction should be stored as an orphan)</p>
<p style="Normal" xid="1070" props="text-align:left; dom-dir:ltr">    // or because the transaction is malformed (in which case the transaction should</p>
<p style="Normal" xid="1071" props="text-align:left; dom-dir:ltr">    // be dropped).  If tx is definitely invalid, fInvalid will be set to true.</p>
<p style="Normal" xid="1072" props="text-align:left; dom-dir:ltr">    fInvalid = false;</p>
<p style="Normal" xid="1073"><c></c></p>
<p style="Normal" xid="1074" props="text-align:left; dom-dir:ltr">    if (IsCoinBase())</p>
<p style="Normal" xid="1075" props="text-align:left; dom-dir:ltr">        return true; // Coinbase transactions have no inputs to fetch.</p>
<p style="Normal" xid="1076"><c></c></p>
<p style="Normal" xid="1077" props="text-align:left; dom-dir:ltr">    for (unsigned int i = 0; i &lt; vin.size(); i++)</p>
<p style="Normal" xid="1078">    {</p>
<p style="Normal" xid="1079" props="text-align:left; dom-dir:ltr">        COutPoint prevout = vin[i].prevout;</p>
<p style="Normal" xid="1080" props="text-align:left; dom-dir:ltr">        if (inputsRet.count(prevout.hash))</p>
<p style="Normal" xid="1081" props="text-align:left; dom-dir:ltr">            continue; // Got it already</p>
<p style="Normal" xid="1082"><c></c></p>
<p style="Normal" xid="1083" props="text-align:left; dom-dir:ltr">        // Read txindex</p>
<p style="Normal" xid="1084" props="text-align:left; dom-dir:ltr">        CTxIndex&amp; txindex = inputsRet[prevout.hash].first;</p>
<p style="Normal" xid="1085" props="text-align:left; dom-dir:ltr">        bool fFound = true;</p>
<p style="Normal" xid="1086" props="text-align:left; dom-dir:ltr">        if ((fBlock || fMiner) &amp;&amp; mapTestPool.count(prevout.hash))</p>
<p style="Normal" xid="1087">        {</p>
<p style="Normal" xid="1088" props="text-align:left; dom-dir:ltr">            // Get txindex from current proposed changes</p>
<p style="Normal" xid="1089" props="text-align:left; dom-dir:ltr">            txindex = mapTestPool.find(prevout.hash)-&gt;second;</p>
<p style="Normal" xid="1090">        }</p>
<p style="Normal" xid="1091" props="text-align:left; dom-dir:ltr">        else</p>
<p style="Normal" xid="1092">        {</p>
<p style="Normal" xid="1093" props="text-align:left; dom-dir:ltr">            // Read txindex from txdb</p>
<p style="Normal" xid="1094" props="text-align:left; dom-dir:ltr">            fFound = txdb.ReadTxIndex(prevout.hash, txindex);</p>
<p style="Normal" xid="1095">        }</p>
<p style="Normal" xid="1096" props="text-align:left; dom-dir:ltr">        if (!fFound &amp;&amp; (fBlock || fMiner))</p>
<p style="Normal" xid="1097" props="text-align:left; dom-dir:ltr">            return fMiner ? false : error("FetchInputs() : %s prev tx %s index entry not found", GetHash().ToString().substr(0,10).c_str(),  prevout.hash.ToString().substr(0,10).c_str());</p>
<p style="Normal" xid="1098"><c></c></p>
<p style="Normal" xid="1099" props="text-align:left; dom-dir:ltr">        // Read txPrev</p>
<p style="Normal" xid="1100" props="text-align:left; dom-dir:ltr">        CTransaction&amp; txPrev = inputsRet[prevout.hash].second;</p>
<p style="Normal" xid="1101" props="text-align:left; dom-dir:ltr">        if (!fFound || txindex.pos == CDiskTxPos(1,1,1))</p>
<p style="Normal" xid="1102">        {</p>
<p style="Normal" xid="1103" props="text-align:left; dom-dir:ltr">            // Get prev tx from single transactions in memory</p>
<p style="Normal" xid="1104">            {</p>
<p style="Normal" xid="1105" props="text-align:left; dom-dir:ltr">                LOCK(mempool.cs);</p>
<p style="Normal" xid="1106" props="text-align:left; dom-dir:ltr">                if (!mempool.exists(prevout.hash))</p>
<p style="Normal" xid="1107" props="text-align:left; dom-dir:ltr">                    return error("FetchInputs() : %s mempool Tx prev not found %s", GetHash().ToString().substr(0,10).c_str(),  prevout.hash.ToString().substr(0,10).c_str());</p>
<p style="Normal" xid="1108" props="text-align:left; dom-dir:ltr">                txPrev = mempool.lookup(prevout.hash);</p>
<p style="Normal" xid="1109">            }</p>
<p style="Normal" xid="1110" props="text-align:left; dom-dir:ltr">            if (!fFound)</p>
<p style="Normal" xid="1111" props="text-align:left; dom-dir:ltr">                txindex.vSpent.resize(txPrev.vout.size());</p>
<p style="Normal" xid="1112">        }</p>
<p style="Normal" xid="1113" props="text-align:left; dom-dir:ltr">        else</p>
<p style="Normal" xid="1114">        {</p>
<p style="Normal" xid="1115" props="text-align:left; dom-dir:ltr">            // Get prev tx from disk</p>
<p style="Normal" xid="1116" props="text-align:left; dom-dir:ltr">            if (!txPrev.ReadFromDisk(txindex.pos))</p>
<p style="Normal" xid="1117" props="text-align:left; dom-dir:ltr">                return error("FetchInputs() : %s ReadFromDisk prev tx %s failed", GetHash().ToString().substr(0,10).c_str(),  prevout.hash.ToString().substr(0,10).c_str());</p>
<p style="Normal" xid="1118">        }</p>
<p style="Normal" xid="1119">    }</p>
<p style="Normal" xid="1120"><c></c></p>
<p style="Normal" xid="1121" props="text-align:left; dom-dir:ltr">    // Make sure all prevout.n's are valid:</p>
<p style="Normal" xid="1122" props="text-align:left; dom-dir:ltr">    for (unsigned int i = 0; i &lt; vin.size(); i++)</p>
<p style="Normal" xid="1123">    {</p>
<p style="Normal" xid="1124" props="text-align:left; dom-dir:ltr">        const COutPoint prevout = vin[i].prevout;</p>
<p style="Normal" xid="1125" props="text-align:left; dom-dir:ltr">        assert(inputsRet.count(prevout.hash) != 0);</p>
<p style="Normal" xid="1126" props="text-align:left; dom-dir:ltr">        const CTxIndex&amp; txindex = inputsRet[prevout.hash].first;</p>
<p style="Normal" xid="1127" props="text-align:left; dom-dir:ltr">        const CTransaction&amp; txPrev = inputsRet[prevout.hash].second;</p>
<p style="Normal" xid="1128" props="text-align:left; dom-dir:ltr">        if (prevout.n &gt;= txPrev.vout.size() || prevout.n &gt;= txindex.vSpent.size())</p>
<p style="Normal" xid="1129">        {</p>
<p style="Normal" xid="1130" props="text-align:left; dom-dir:ltr">            // Revisit this if/when transaction replacement is implemented and allows</p>
<p style="Normal" xid="1131" props="text-align:left; dom-dir:ltr">            // adding inputs:</p>
<p style="Normal" xid="1132" props="text-align:left; dom-dir:ltr">            fInvalid = true;</p>
<p style="Normal" xid="1133" props="text-align:left; dom-dir:ltr">            return DoS(100, error("FetchInputs() : %s prevout.n out of range %d %d %d prev tx %s\n%s", GetHash().ToString().substr(0,10).c_str(), prevout.n, txPrev.vout.size(), txindex.vSpent.size(), prevout.hash.ToString().substr(0,10).c_str(), txPrev.ToString().c_str()));</p>
<p style="Normal" xid="1134">        }</p>
<p style="Normal" xid="1135">    }</p>
<p style="Normal" xid="1136"><c></c></p>
<p style="Normal" xid="1137" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="1138">}</p>
<p style="Normal" xid="1139"><c></c></p>
<p style="Normal" xid="1140" props="text-align:left; dom-dir:ltr">const CTxOut&amp; CTransaction::GetOutputFor(const CTxIn&amp; input, const MapPrevTx&amp; inputs) const</p>
<p style="Normal" xid="1141">{</p>
<p style="Normal" xid="1142" props="text-align:left; dom-dir:ltr">    MapPrevTx::const_iterator mi = inputs.find(input.prevout.hash);</p>
<p style="Normal" xid="1143" props="text-align:left; dom-dir:ltr">    if (mi == inputs.end())</p>
<p style="Normal" xid="1144" props="text-align:left; dom-dir:ltr">        throw std::runtime_error("CTransaction::GetOutputFor() : prevout.hash not found");</p>
<p style="Normal" xid="1145"><c></c></p>
<p style="Normal" xid="1146" props="text-align:left; dom-dir:ltr">    const CTransaction&amp; txPrev = (mi-&gt;second).second;</p>
<p style="Normal" xid="1147" props="text-align:left; dom-dir:ltr">    if (input.prevout.n &gt;= txPrev.vout.size())</p>
<p style="Normal" xid="1148" props="text-align:left; dom-dir:ltr">        throw std::runtime_error("CTransaction::GetOutputFor() : prevout.n out of range");</p>
<p style="Normal" xid="1149"><c></c></p>
<p style="Normal" xid="1150" props="text-align:left; dom-dir:ltr">    return txPrev.vout[input.prevout.n];</p>
<p style="Normal" xid="1151">}</p>
<p style="Normal" xid="1152"><c></c></p>
<p style="Normal" xid="1153" props="text-align:left; dom-dir:ltr">int64 CTransaction::GetValueIn(const MapPrevTx&amp; inputs) const</p>
<p style="Normal" xid="1154">{</p>
<p style="Normal" xid="1155" props="text-align:left; dom-dir:ltr">    if (IsCoinBase())</p>
<p style="Normal" xid="1156" props="text-align:left; dom-dir:ltr">        return 0;</p>
<p style="Normal" xid="1157"><c></c></p>
<p style="Normal" xid="1158" props="text-align:left; dom-dir:ltr">    int64 nResult = 0;</p>
<p style="Normal" xid="1159" props="text-align:left; dom-dir:ltr">    for (unsigned int i = 0; i &lt; vin.size(); i++)</p>
<p style="Normal" xid="1160">    {</p>
<p style="Normal" xid="1161" props="text-align:left; dom-dir:ltr">        nResult += GetOutputFor(vin[i], inputs).nValue;</p>
<p style="Normal" xid="1162">    }</p>
<p style="Normal" xid="1163" props="text-align:left; dom-dir:ltr">    return nResult;</p>
<p style="Normal" xid="1164"><c></c></p>
<p style="Normal" xid="1165">}</p>
<p style="Normal" xid="1166"><c></c></p>
<p style="Normal" xid="1167" props="text-align:left; dom-dir:ltr">unsigned int CTransaction::GetP2SHSigOpCount(const MapPrevTx&amp; inputs) const</p>
<p style="Normal" xid="1168">{</p>
<p style="Normal" xid="1169" props="text-align:left; dom-dir:ltr">    if (IsCoinBase())</p>
<p style="Normal" xid="1170" props="text-align:left; dom-dir:ltr">        return 0;</p>
<p style="Normal" xid="1171"><c></c></p>
<p style="Normal" xid="1172" props="text-align:left; dom-dir:ltr">    unsigned int nSigOps = 0;</p>
<p style="Normal" xid="1173" props="text-align:left; dom-dir:ltr">    for (unsigned int i = 0; i &lt; vin.size(); i++)</p>
<p style="Normal" xid="1174">    {</p>
<p style="Normal" xid="1175" props="text-align:left; dom-dir:ltr">        const CTxOut&amp; prevout = GetOutputFor(vin[i], inputs);</p>
<p style="Normal" xid="1176" props="text-align:left; dom-dir:ltr">        if (prevout.scriptPubKey.IsPayToScriptHash())</p>
<p style="Normal" xid="1177" props="text-align:left; dom-dir:ltr">            nSigOps += prevout.scriptPubKey.GetSigOpCount(vin[i].scriptSig);</p>
<p style="Normal" xid="1178">    }</p>
<p style="Normal" xid="1179" props="text-align:left; dom-dir:ltr">    return nSigOps;</p>
<p style="Normal" xid="1180">}</p>
<p style="Normal" xid="1181"><c></c></p>
<p style="Normal" xid="1182" props="text-align:left; dom-dir:ltr">bool CTransaction::ConnectInputs(MapPrevTx inputs,</p>
<p style="Normal" xid="1183" props="text-align:left; dom-dir:ltr">                                 map&lt;uint256, CTxIndex&gt;&amp; mapTestPool, const CDiskTxPos&amp; posThisTx,</p>
<p style="Normal" xid="1184" props="text-align:left; dom-dir:ltr">                                 const CBlockIndex* pindexBlock, bool fBlock, bool fMiner, bool fStrictPayToScriptHash)</p>
<p style="Normal" xid="1185">{</p>
<p style="Normal" xid="1186" props="text-align:left; dom-dir:ltr">    // Take over previous transactions' spent pointers</p>
<p style="Normal" xid="1187" props="text-align:left; dom-dir:ltr">    // fBlock is true when this is called from AcceptBlock when a new best-block is added to the blockchain</p>
<p style="Normal" xid="1188" props="text-align:left; dom-dir:ltr">    // fMiner is true when called from the internal flightcoin miner</p>
<p style="Normal" xid="1189" props="text-align:left; dom-dir:ltr">    // ... both are false when called from CTransaction::AcceptToMemoryPool</p>
<p style="Normal" xid="1190" props="text-align:left; dom-dir:ltr">    if (!IsCoinBase())</p>
<p style="Normal" xid="1191">    {</p>
<p style="Normal" xid="1192" props="text-align:left; dom-dir:ltr">        int64 nValueIn = 0;</p>
<p style="Normal" xid="1193" props="text-align:left; dom-dir:ltr">        int64 nFees = 0;</p>
<p style="Normal" xid="1194" props="text-align:left; dom-dir:ltr">        for (unsigned int i = 0; i &lt; vin.size(); i++)</p>
<p style="Normal" xid="1195">        {</p>
<p style="Normal" xid="1196" props="text-align:left; dom-dir:ltr">            COutPoint prevout = vin[i].prevout;</p>
<p style="Normal" xid="1197" props="text-align:left; dom-dir:ltr">            assert(inputs.count(prevout.hash) &gt; 0);</p>
<p style="Normal" xid="1198" props="text-align:left; dom-dir:ltr">            CTxIndex&amp; txindex = inputs[prevout.hash].first;</p>
<p style="Normal" xid="1199" props="text-align:left; dom-dir:ltr">            CTransaction&amp; txPrev = inputs[prevout.hash].second;</p>
<p style="Normal" xid="1200"><c></c></p>
<p style="Normal" xid="1201" props="text-align:left; dom-dir:ltr">            if (prevout.n &gt;= txPrev.vout.size() || prevout.n &gt;= txindex.vSpent.size())</p>
<p style="Normal" xid="1202" props="text-align:left; dom-dir:ltr">                return DoS(100, error("ConnectInputs() : %s prevout.n out of range %d %d %d prev tx %s\n%s", GetHash().ToString().substr(0,10).c_str(), prevout.n, txPrev.vout.size(), txindex.vSpent.size(), prevout.hash.ToString().substr(0,10).c_str(), txPrev.ToString().c_str()));</p>
<p style="Normal" xid="1203"><c></c></p>
<p style="Normal" xid="1204" props="text-align:left; dom-dir:ltr">            // If prev is coinbase, check that it's matured</p>
<p style="Normal" xid="1205" props="text-align:left; dom-dir:ltr">            if (txPrev.IsCoinBase())</p>
<p style="Normal" xid="1206" props="text-align:left; dom-dir:ltr">                for (const CBlockIndex* pindex = pindexBlock; pindex &amp;&amp; pindexBlock-&gt;nHeight - pindex-&gt;nHeight &lt; COINBASE_MATURITY; pindex = pindex-&gt;pprev)</p>
<p style="Normal" xid="1207" props="text-align:left; dom-dir:ltr">                    if (pindex-&gt;nBlockPos == txindex.pos.nBlockPos &amp;&amp; pindex-&gt;nFile == txindex.pos.nFile)</p>
<p style="Normal" xid="1208" props="text-align:left; dom-dir:ltr">                        return error("ConnectInputs() : tried to spend coinbase at depth %d", pindexBlock-&gt;nHeight - pindex-&gt;nHeight);</p>
<p style="Normal" xid="1209"><c></c></p>
<p style="Normal" xid="1210" props="text-align:left; dom-dir:ltr">            // Check for negative or overflow input values</p>
<p style="Normal" xid="1211" props="text-align:left; dom-dir:ltr">            nValueIn += txPrev.vout[prevout.n].nValue;</p>
<p style="Normal" xid="1212" props="text-align:left; dom-dir:ltr">            if (!MoneyRange(txPrev.vout[prevout.n].nValue) || !MoneyRange(nValueIn))</p>
<p style="Normal" xid="1213" props="text-align:left; dom-dir:ltr">                return DoS(100, error("ConnectInputs() : txin values out of range"));</p>
<p style="Normal" xid="1214"><c></c></p>
<p style="Normal" xid="1215">        }</p>
<p style="Normal" xid="1216" props="text-align:left; dom-dir:ltr">        // The first loop above does all the inexpensive checks.</p>
<p style="Normal" xid="1217" props="text-align:left; dom-dir:ltr">        // Only if ALL inputs pass do we perform expensive ECDSA signature checks.</p>
<p style="Normal" xid="1218" props="text-align:left; dom-dir:ltr">        // Helps prevent CPU exhaustion attacks.</p>
<p style="Normal" xid="1219" props="text-align:left; dom-dir:ltr">        for (unsigned int i = 0; i &lt; vin.size(); i++)</p>
<p style="Normal" xid="1220">        {</p>
<p style="Normal" xid="1221" props="text-align:left; dom-dir:ltr">            COutPoint prevout = vin[i].prevout;</p>
<p style="Normal" xid="1222" props="text-align:left; dom-dir:ltr">            assert(inputs.count(prevout.hash) &gt; 0);</p>
<p style="Normal" xid="1223" props="text-align:left; dom-dir:ltr">            CTxIndex&amp; txindex = inputs[prevout.hash].first;</p>
<p style="Normal" xid="1224" props="text-align:left; dom-dir:ltr">            CTransaction&amp; txPrev = inputs[prevout.hash].second;</p>
<p style="Normal" xid="1225"><c></c></p>
<p style="Normal" xid="1226" props="text-align:left; dom-dir:ltr">            // Check for conflicts (double-spend)</p>
<p style="Normal" xid="1227" props="text-align:left; dom-dir:ltr">            // This doesn't trigger the DoS code on purpose; if it did, it would make it easier</p>
<p style="Normal" xid="1228" props="text-align:left; dom-dir:ltr">            // for an attacker to attempt to split the network.</p>
<p style="Normal" xid="1229" props="text-align:left; dom-dir:ltr">            if (!txindex.vSpent[prevout.n].IsNull())</p>
<p style="Normal" xid="1230" props="text-align:left; dom-dir:ltr">                return fMiner ? false : error("ConnectInputs() : %s prev tx already used at %s", GetHash().ToString().substr(0,10).c_str(), txindex.vSpent[prevout.n].ToString().c_str());</p>
<p style="Normal" xid="1231"><c></c></p>
<p style="Normal" xid="1232" props="text-align:left; dom-dir:ltr">            // Skip ECDSA signature verification when connecting blocks (fBlock=true)</p>
<p style="Normal" xid="1233" props="text-align:left; dom-dir:ltr">            // before the last blockchain checkpoint. This is safe because block merkle hashes are</p>
<p style="Normal" xid="1234" props="text-align:left; dom-dir:ltr">            // still computed and checked, and any change will be caught at the next checkpoint.</p>
<p style="Normal" xid="1235" props="text-align:left; dom-dir:ltr">            if (!(fBlock &amp;&amp; (nBestHeight &lt; Checkpoints::GetTotalBlocksEstimate())))</p>
<p style="Normal" xid="1236">            {</p>
<p style="Normal" xid="1237" props="text-align:left; dom-dir:ltr">                // Verify signature</p>
<p style="Normal" xid="1238" props="text-align:left; dom-dir:ltr">                if (!VerifySignature(txPrev, *this, i, fStrictPayToScriptHash, 0))</p>
<p style="Normal" xid="1239">                {</p>
<p style="Normal" xid="1240" props="text-align:left; dom-dir:ltr">                    // only during transition phase for P2SH: do not invoke anti-DoS code for</p>
<p style="Normal" xid="1241" props="text-align:left; dom-dir:ltr">                    // potentially old clients relaying bad P2SH transactions</p>
<p style="Normal" xid="1242" props="text-align:left; dom-dir:ltr">                    if (fStrictPayToScriptHash &amp;&amp; VerifySignature(txPrev, *this, i, false, 0))</p>
<p style="Normal" xid="1243" props="text-align:left; dom-dir:ltr">                        return error("ConnectInputs() : %s P2SH VerifySignature failed", GetHash().ToString().substr(0,10).c_str());</p>
<p style="Normal" xid="1244"><c></c></p>
<p style="Normal" xid="1245" props="text-align:left; dom-dir:ltr">                    return DoS(100,error("ConnectInputs() : %s VerifySignature failed", GetHash().ToString().substr(0,10).c_str()));</p>
<p style="Normal" xid="1246">                }</p>
<p style="Normal" xid="1247">            }</p>
<p style="Normal" xid="1248"><c></c></p>
<p style="Normal" xid="1249" props="text-align:left; dom-dir:ltr">            // Mark outpoints as spent</p>
<p style="Normal" xid="1250" props="text-align:left; dom-dir:ltr">            txindex.vSpent[prevout.n] = posThisTx;</p>
<p style="Normal" xid="1251"><c></c></p>
<p style="Normal" xid="1252" props="text-align:left; dom-dir:ltr">            // Write back</p>
<p style="Normal" xid="1253" props="text-align:left; dom-dir:ltr">            if (fBlock || fMiner)</p>
<p style="Normal" xid="1254">            {</p>
<p style="Normal" xid="1255" props="text-align:left; dom-dir:ltr">                mapTestPool[prevout.hash] = txindex;</p>
<p style="Normal" xid="1256">            }</p>
<p style="Normal" xid="1257">        }</p>
<p style="Normal" xid="1258"><c></c></p>
<p style="Normal" xid="1259" props="text-align:left; dom-dir:ltr">        if (nValueIn &lt; GetValueOut())</p>
<p style="Normal" xid="1260" props="text-align:left; dom-dir:ltr">            return DoS(100, error("ConnectInputs() : %s value in &lt; value out", GetHash().ToString().substr(0,10).c_str()));</p>
<p style="Normal" xid="1261"><c></c></p>
<p style="Normal" xid="1262" props="text-align:left; dom-dir:ltr">        // Tally transaction fees</p>
<p style="Normal" xid="1263" props="text-align:left; dom-dir:ltr">        int64 nTxFee = nValueIn - GetValueOut();</p>
<p style="Normal" xid="1264" props="text-align:left; dom-dir:ltr">        if (nTxFee &lt; 0)</p>
<p style="Normal" xid="1265" props="text-align:left; dom-dir:ltr">            return DoS(100, error("ConnectInputs() : %s nTxFee &lt; 0", GetHash().ToString().substr(0,10).c_str()));</p>
<p style="Normal" xid="1266" props="text-align:left; dom-dir:ltr">        nFees += nTxFee;</p>
<p style="Normal" xid="1267" props="text-align:left; dom-dir:ltr">        if (!MoneyRange(nFees))</p>
<p style="Normal" xid="1268" props="text-align:left; dom-dir:ltr">            return DoS(100, error("ConnectInputs() : nFees out of range"));</p>
<p style="Normal" xid="1269">    }</p>
<p style="Normal" xid="1270"><c></c></p>
<p style="Normal" xid="1271" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="1272">}</p>
<p style="Normal" xid="1273"><c></c></p>
<p style="Normal" xid="1274"><c></c></p>
<p style="Normal" xid="1275" props="text-align:left; dom-dir:ltr">bool CTransaction::ClientConnectInputs()</p>
<p style="Normal" xid="1276">{</p>
<p style="Normal" xid="1277" props="text-align:left; dom-dir:ltr">    if (IsCoinBase())</p>
<p style="Normal" xid="1278" props="text-align:left; dom-dir:ltr">        return false;</p>
<p style="Normal" xid="1279"><c></c></p>
<p style="Normal" xid="1280" props="text-align:left; dom-dir:ltr">    // Take over previous transactions' spent pointers</p>
<p style="Normal" xid="1281">    {</p>
<p style="Normal" xid="1282" props="text-align:left; dom-dir:ltr">        LOCK(mempool.cs);</p>
<p style="Normal" xid="1283" props="text-align:left; dom-dir:ltr">        int64 nValueIn = 0;</p>
<p style="Normal" xid="1284" props="text-align:left; dom-dir:ltr">        for (unsigned int i = 0; i &lt; vin.size(); i++)</p>
<p style="Normal" xid="1285">        {</p>
<p style="Normal" xid="1286" props="text-align:left; dom-dir:ltr">            // Get prev tx from single transactions in memory</p>
<p style="Normal" xid="1287" props="text-align:left; dom-dir:ltr">            COutPoint prevout = vin[i].prevout;</p>
<p style="Normal" xid="1288" props="text-align:left; dom-dir:ltr">            if (!mempool.exists(prevout.hash))</p>
<p style="Normal" xid="1289" props="text-align:left; dom-dir:ltr">                return false;</p>
<p style="Normal" xid="1290" props="text-align:left; dom-dir:ltr">            CTransaction&amp; txPrev = mempool.lookup(prevout.hash);</p>
<p style="Normal" xid="1291"><c></c></p>
<p style="Normal" xid="1292" props="text-align:left; dom-dir:ltr">            if (prevout.n &gt;= txPrev.vout.size())</p>
<p style="Normal" xid="1293" props="text-align:left; dom-dir:ltr">                return false;</p>
<p style="Normal" xid="1294"><c></c></p>
<p style="Normal" xid="1295" props="text-align:left; dom-dir:ltr">            // Verify signature</p>
<p style="Normal" xid="1296" props="text-align:left; dom-dir:ltr">            if (!VerifySignature(txPrev, *this, i, true, 0))</p>
<p style="Normal" xid="1297" props="text-align:left; dom-dir:ltr">                return error("ConnectInputs() : VerifySignature failed");</p>
<p style="Normal" xid="1298"><c></c></p>
<p style="Normal" xid="1299" props="text-align:left; dom-dir:ltr">            ///// this is redundant with the mempool.mapNextTx stuff,</p>
<p style="Normal" xid="1300" props="text-align:left; dom-dir:ltr">            ///// not sure which I want to get rid of</p>
<p style="Normal" xid="1301" props="text-align:left; dom-dir:ltr">            ///// this has to go away now that posNext is gone</p>
<p style="Normal" xid="1302" props="text-align:left; dom-dir:ltr">            // // Check for conflicts</p>
<p style="Normal" xid="1303" props="text-align:left; dom-dir:ltr">            // if (!txPrev.vout[prevout.n].posNext.IsNull())</p>
<p style="Normal" xid="1304" props="text-align:left; dom-dir:ltr">            //     return error("ConnectInputs() : prev tx already used");</p>
<p style="Normal" xid="1305">            //</p>
<p style="Normal" xid="1306" props="text-align:left; dom-dir:ltr">            // // Flag outpoints as used</p>
<p style="Normal" xid="1307" props="text-align:left; dom-dir:ltr">            // txPrev.vout[prevout.n].posNext = posThisTx;</p>
<p style="Normal" xid="1308"><c></c></p>
<p style="Normal" xid="1309" props="text-align:left; dom-dir:ltr">            nValueIn += txPrev.vout[prevout.n].nValue;</p>
<p style="Normal" xid="1310"><c></c></p>
<p style="Normal" xid="1311" props="text-align:left; dom-dir:ltr">            if (!MoneyRange(txPrev.vout[prevout.n].nValue) || !MoneyRange(nValueIn))</p>
<p style="Normal" xid="1312" props="text-align:left; dom-dir:ltr">                return error("ClientConnectInputs() : txin values out of range");</p>
<p style="Normal" xid="1313">        }</p>
<p style="Normal" xid="1314" props="text-align:left; dom-dir:ltr">        if (GetValueOut() &gt; nValueIn)</p>
<p style="Normal" xid="1315" props="text-align:left; dom-dir:ltr">            return false;</p>
<p style="Normal" xid="1316">    }</p>
<p style="Normal" xid="1317"><c></c></p>
<p style="Normal" xid="1318" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="1319">}</p>
<p style="Normal" xid="1320"><c></c></p>
<p style="Normal" xid="1321"><c></c></p>
<p style="Normal" xid="1322"><c></c></p>
<p style="Normal" xid="1323"><c></c></p>
<p style="Normal" xid="1324" props="text-align:left; dom-dir:ltr">bool CBlock::DisconnectBlock(CTxDB&amp; txdb, CBlockIndex* pindex)</p>
<p style="Normal" xid="1325">{</p>
<p style="Normal" xid="1326" props="text-align:left; dom-dir:ltr">    // Disconnect in reverse order</p>
<p style="Normal" xid="1327" props="text-align:left; dom-dir:ltr">    for (int i = vtx.size()-1; i &gt;= 0; i--)</p>
<p style="Normal" xid="1328" props="text-align:left; dom-dir:ltr">        if (!vtx[i].DisconnectInputs(txdb))</p>
<p style="Normal" xid="1329" props="text-align:left; dom-dir:ltr">            return false;</p>
<p style="Normal" xid="1330"><c></c></p>
<p style="Normal" xid="1331" props="text-align:left; dom-dir:ltr">    // Update block index on disk without changing it in memory.</p>
<p style="Normal" xid="1332" props="text-align:left; dom-dir:ltr">    // The memory index structure will be changed after the db commits.</p>
<p style="Normal" xid="1333" props="text-align:left; dom-dir:ltr">    if (pindex-&gt;pprev)</p>
<p style="Normal" xid="1334">    {</p>
<p style="Normal" xid="1335" props="text-align:left; dom-dir:ltr">        CDiskBlockIndex blockindexPrev(pindex-&gt;pprev);</p>
<p style="Normal" xid="1336" props="text-align:left; dom-dir:ltr">        blockindexPrev.hashNext = 0;</p>
<p style="Normal" xid="1337" props="text-align:left; dom-dir:ltr">        if (!txdb.WriteBlockIndex(blockindexPrev))</p>
<p style="Normal" xid="1338" props="text-align:left; dom-dir:ltr">            return error("DisconnectBlock() : WriteBlockIndex failed");</p>
<p style="Normal" xid="1339">    }</p>
<p style="Normal" xid="1340"><c></c></p>
<p style="Normal" xid="1341" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="1342">}</p>
<p style="Normal" xid="1343"><c></c></p>
<p style="Normal" xid="1344" props="text-align:left; dom-dir:ltr">bool CBlock::ConnectBlock(CTxDB&amp; txdb, CBlockIndex* pindex)</p>
<p style="Normal" xid="1345">{</p>
<p style="Normal" xid="1346" props="text-align:left; dom-dir:ltr">    // Check it again in case a previous version let a bad block in</p>
<p style="Normal" xid="1347" props="text-align:left; dom-dir:ltr">    if (!CheckBlock())</p>
<p style="Normal" xid="1348" props="text-align:left; dom-dir:ltr">        return false;</p>
<p style="Normal" xid="1349"><c></c></p>
<p style="Normal" xid="1350" props="text-align:left; dom-dir:ltr">    // Do not allow blocks that contain transactions which 'overwrite' older transactions,</p>
<p style="Normal" xid="1351" props="text-align:left; dom-dir:ltr">    // unless those are already completely spent.</p>
<p style="Normal" xid="1352" props="text-align:left; dom-dir:ltr">    // If such overwrites are allowed, coinbases and transactions depending upon those</p>
<p style="Normal" xid="1353" props="text-align:left; dom-dir:ltr">    // can be duplicated to remove the ability to spend the first instance -- even after</p>
<p style="Normal" xid="1354" props="text-align:left; dom-dir:ltr">    // being sent to another address.</p>
<p style="Normal" xid="1355" props="text-align:left; dom-dir:ltr">    // See BIP30 and http://r6.ca/blog/20120206T005236Z.html for more information.</p>
<p style="Normal" xid="1356" props="text-align:left; dom-dir:ltr">    // This logic is not necessary for memory pool transactions, as AcceptToMemoryPool</p>
<p style="Normal" xid="1357" props="text-align:left; dom-dir:ltr">    // already refuses previously-known transaction id's entirely.</p>
<p style="Normal" xid="1358" props="text-align:left; dom-dir:ltr">    // This rule applies to all blocks whose timestamp is after October 1, 2012, 0:00 UTC.</p>
<p style="Normal" xid="1359" props="text-align:left; dom-dir:ltr">    int64 nBIP30SwitchTime = 1349049600;</p>
<p style="Normal" xid="1360" props="text-align:left; dom-dir:ltr">    bool fEnforceBIP30 = (pindex-&gt;nTime &gt; nBIP30SwitchTime);</p>
<p style="Normal" xid="1361"><c></c></p>
<p style="Normal" xid="1362" props="text-align:left; dom-dir:ltr">    // BIP16 didn't become active until October 1 2012</p>
<p style="Normal" xid="1363" props="text-align:left; dom-dir:ltr">    int64 nBIP16SwitchTime = 1349049600;</p>
<p style="Normal" xid="1364" props="text-align:left; dom-dir:ltr">    bool fStrictPayToScriptHash = (pindex-&gt;nTime &gt;= nBIP16SwitchTime);</p>
<p style="Normal" xid="1365"><c></c></p>
<p style="Normal" xid="1366" props="text-align:left; dom-dir:ltr">    //// issue here: it doesn't know the version</p>
<p style="Normal" xid="1367" props="text-align:left; dom-dir:ltr">    unsigned int nTxPos = pindex-&gt;nBlockPos + ::GetSerializeSize(CBlock(), SER_DISK, CLIENT_VERSION) - 1 + GetSizeOfCompactSize(vtx.size());</p>
<p style="Normal" xid="1368"><c></c></p>
<p style="Normal" xid="1369" props="text-align:left; dom-dir:ltr">    map&lt;uint256, CTxIndex&gt; mapQueuedChanges;</p>
<p style="Normal" xid="1370" props="text-align:left; dom-dir:ltr">    int64 nFees = 0;</p>
<p style="Normal" xid="1371" props="text-align:left; dom-dir:ltr">    unsigned int nSigOps = 0;</p>
<p style="Normal" xid="1372" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(CTransaction&amp; tx, vtx)</p>
<p style="Normal" xid="1373">    {</p>
<p style="Normal" xid="1374" props="text-align:left; dom-dir:ltr">        uint256 hashTx = tx.GetHash();</p>
<p style="Normal" xid="1375"><c></c></p>
<p style="Normal" xid="1376" props="text-align:left; dom-dir:ltr">        if (fEnforceBIP30) {</p>
<p style="Normal" xid="1377" props="text-align:left; dom-dir:ltr">            CTxIndex txindexOld;</p>
<p style="Normal" xid="1378" props="text-align:left; dom-dir:ltr">            if (txdb.ReadTxIndex(hashTx, txindexOld)) {</p>
<p style="Normal" xid="1379" props="text-align:left; dom-dir:ltr">                BOOST_FOREACH(CDiskTxPos &amp;pos, txindexOld.vSpent)</p>
<p style="Normal" xid="1380" props="text-align:left; dom-dir:ltr">                    if (pos.IsNull())</p>
<p style="Normal" xid="1381" props="text-align:left; dom-dir:ltr">                        return false;</p>
<p style="Normal" xid="1382">            }</p>
<p style="Normal" xid="1383">        }</p>
<p style="Normal" xid="1384"><c></c></p>
<p style="Normal" xid="1385" props="text-align:left; dom-dir:ltr">        nSigOps += tx.GetLegacySigOpCount();</p>
<p style="Normal" xid="1386" props="text-align:left; dom-dir:ltr">        if (nSigOps &gt; MAX_BLOCK_SIGOPS)</p>
<p style="Normal" xid="1387" props="text-align:left; dom-dir:ltr">            return DoS(100, error("ConnectBlock() : too many sigops"));</p>
<p style="Normal" xid="1388"><c></c></p>
<p style="Normal" xid="1389" props="text-align:left; dom-dir:ltr">        CDiskTxPos posThisTx(pindex-&gt;nFile, pindex-&gt;nBlockPos, nTxPos);</p>
<p style="Normal" xid="1390" props="text-align:left; dom-dir:ltr">        nTxPos += ::GetSerializeSize(tx, SER_DISK, CLIENT_VERSION);</p>
<p style="Normal" xid="1391"><c></c></p>
<p style="Normal" xid="1392" props="text-align:left; dom-dir:ltr">        MapPrevTx mapInputs;</p>
<p style="Normal" xid="1393" props="text-align:left; dom-dir:ltr">        if (!tx.IsCoinBase())</p>
<p style="Normal" xid="1394">        {</p>
<p style="Normal" xid="1395" props="text-align:left; dom-dir:ltr">            bool fInvalid;</p>
<p style="Normal" xid="1396" props="text-align:left; dom-dir:ltr">            if (!tx.FetchInputs(txdb, mapQueuedChanges, true, false, mapInputs, fInvalid))</p>
<p style="Normal" xid="1397" props="text-align:left; dom-dir:ltr">                return false;</p>
<p style="Normal" xid="1398"><c></c></p>
<p style="Normal" xid="1399" props="text-align:left; dom-dir:ltr">            if (fStrictPayToScriptHash)</p>
<p style="Normal" xid="1400">            {</p>
<p style="Normal" xid="1401" props="text-align:left; dom-dir:ltr">                // Add in sigops done by pay-to-script-hash inputs;</p>
<p style="Normal" xid="1402" props="text-align:left; dom-dir:ltr">                // this is to prevent a "rogue miner" from creating</p>
<p style="Normal" xid="1403" props="text-align:left; dom-dir:ltr">                // an incredibly-expensive-to-validate block.</p>
<p style="Normal" xid="1404" props="text-align:left; dom-dir:ltr">                nSigOps += tx.GetP2SHSigOpCount(mapInputs);</p>
<p style="Normal" xid="1405" props="text-align:left; dom-dir:ltr">                if (nSigOps &gt; MAX_BLOCK_SIGOPS)</p>
<p style="Normal" xid="1406" props="text-align:left; dom-dir:ltr">                    return DoS(100, error("ConnectBlock() : too many sigops"));</p>
<p style="Normal" xid="1407">            }</p>
<p style="Normal" xid="1408"><c></c></p>
<p style="Normal" xid="1409" props="text-align:left; dom-dir:ltr">            nFees += tx.GetValueIn(mapInputs)-tx.GetValueOut();</p>
<p style="Normal" xid="1410"><c></c></p>
<p style="Normal" xid="1411" props="text-align:left; dom-dir:ltr">            if (!tx.ConnectInputs(mapInputs, mapQueuedChanges, posThisTx, pindex, true, false, fStrictPayToScriptHash))</p>
<p style="Normal" xid="1412" props="text-align:left; dom-dir:ltr">                return false;</p>
<p style="Normal" xid="1413">        }</p>
<p style="Normal" xid="1414"><c></c></p>
<p style="Normal" xid="1415" props="text-align:left; dom-dir:ltr">        mapQueuedChanges[hashTx] = CTxIndex(posThisTx, tx.vout.size());</p>
<p style="Normal" xid="1416">    }</p>
<p style="Normal" xid="1417"><c></c></p>
<p style="Normal" xid="1418" props="text-align:left; dom-dir:ltr">    // Write queued txindex changes</p>
<p style="Normal" xid="1419" props="text-align:left; dom-dir:ltr">    for (map&lt;uint256, CTxIndex&gt;::iterator mi = mapQueuedChanges.begin(); mi != mapQueuedChanges.end(); ++mi)</p>
<p style="Normal" xid="1420">    {</p>
<p style="Normal" xid="1421" props="text-align:left; dom-dir:ltr">        if (!txdb.UpdateTxIndex((*mi).first, (*mi).second))</p>
<p style="Normal" xid="1422" props="text-align:left; dom-dir:ltr">            return error("ConnectBlock() : UpdateTxIndex failed");</p>
<p style="Normal" xid="1423">    }</p>
<p style="Normal" xid="1424"><c></c></p>
<p style="Normal" xid="1425" props="text-align:left; dom-dir:ltr">    if (vtx[0].GetValueOut() &gt; GetBlockValue(pindex-&gt;nHeight, nFees))</p>
<p style="Normal" xid="1426" props="text-align:left; dom-dir:ltr">        return false;</p>
<p style="Normal" xid="1427"><c></c></p>
<p style="Normal" xid="1428" props="text-align:left; dom-dir:ltr">    // Update block index on disk without changing it in memory.</p>
<p style="Normal" xid="1429" props="text-align:left; dom-dir:ltr">    // The memory index structure will be changed after the db commits.</p>
<p style="Normal" xid="1430" props="text-align:left; dom-dir:ltr">    if (pindex-&gt;pprev)</p>
<p style="Normal" xid="1431">    {</p>
<p style="Normal" xid="1432" props="text-align:left; dom-dir:ltr">        CDiskBlockIndex blockindexPrev(pindex-&gt;pprev);</p>
<p style="Normal" xid="1433" props="text-align:left; dom-dir:ltr">        blockindexPrev.hashNext = pindex-&gt;GetBlockHash();</p>
<p style="Normal" xid="1434" props="text-align:left; dom-dir:ltr">        if (!txdb.WriteBlockIndex(blockindexPrev))</p>
<p style="Normal" xid="1435" props="text-align:left; dom-dir:ltr">            return error("ConnectBlock() : WriteBlockIndex failed");</p>
<p style="Normal" xid="1436">    }</p>
<p style="Normal" xid="1437"><c></c></p>
<p style="Normal" xid="1438" props="text-align:left; dom-dir:ltr">    // Watch for transactions paying to me</p>
<p style="Normal" xid="1439" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(CTransaction&amp; tx, vtx)</p>
<p style="Normal" xid="1440" props="text-align:left; dom-dir:ltr">        SyncWithWallets(tx, this, true);</p>
<p style="Normal" xid="1441"><c></c></p>
<p style="Normal" xid="1442" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="1443">}</p>
<p style="Normal" xid="1444"><c></c></p>
<p style="Normal" xid="1445" props="text-align:left; dom-dir:ltr">bool static Reorganize(CTxDB&amp; txdb, CBlockIndex* pindexNew)</p>
<p style="Normal" xid="1446">{</p>
<p style="Normal" xid="1447" props="text-align:left; dom-dir:ltr">    printf("REORGANIZE\n");</p>
<p style="Normal" xid="1448"><c></c></p>
<p style="Normal" xid="1449" props="text-align:left; dom-dir:ltr">    // Find the fork</p>
<p style="Normal" xid="1450" props="text-align:left; dom-dir:ltr">    CBlockIndex* pfork = pindexBest;</p>
<p style="Normal" xid="1451" props="text-align:left; dom-dir:ltr">    CBlockIndex* plonger = pindexNew;</p>
<p style="Normal" xid="1452" props="text-align:left; dom-dir:ltr">    while (pfork != plonger)</p>
<p style="Normal" xid="1453">    {</p>
<p style="Normal" xid="1454" props="text-align:left; dom-dir:ltr">        while (plonger-&gt;nHeight &gt; pfork-&gt;nHeight)</p>
<p style="Normal" xid="1455" props="text-align:left; dom-dir:ltr">            if (!(plonger = plonger-&gt;pprev))</p>
<p style="Normal" xid="1456" props="text-align:left; dom-dir:ltr">                return error("Reorganize() : plonger-&gt;pprev is null");</p>
<p style="Normal" xid="1457" props="text-align:left; dom-dir:ltr">        if (pfork == plonger)</p>
<p style="Normal" xid="1458" props="text-align:left; dom-dir:ltr">            break;</p>
<p style="Normal" xid="1459" props="text-align:left; dom-dir:ltr">        if (!(pfork = pfork-&gt;pprev))</p>
<p style="Normal" xid="1460" props="text-align:left; dom-dir:ltr">            return error("Reorganize() : pfork-&gt;pprev is null");</p>
<p style="Normal" xid="1461">    }</p>
<p style="Normal" xid="1462"><c></c></p>
<p style="Normal" xid="1463" props="text-align:left; dom-dir:ltr">    // List of what to disconnect</p>
<p style="Normal" xid="1464" props="text-align:left; dom-dir:ltr">    vector&lt;CBlockIndex*&gt; vDisconnect;</p>
<p style="Normal" xid="1465" props="text-align:left; dom-dir:ltr">    for (CBlockIndex* pindex = pindexBest; pindex != pfork; pindex = pindex-&gt;pprev)</p>
<p style="Normal" xid="1466" props="text-align:left; dom-dir:ltr">        vDisconnect.push_back(pindex);</p>
<p style="Normal" xid="1467"><c></c></p>
<p style="Normal" xid="1468" props="text-align:left; dom-dir:ltr">    // List of what to connect</p>
<p style="Normal" xid="1469" props="text-align:left; dom-dir:ltr">    vector&lt;CBlockIndex*&gt; vConnect;</p>
<p style="Normal" xid="1470" props="text-align:left; dom-dir:ltr">    for (CBlockIndex* pindex = pindexNew; pindex != pfork; pindex = pindex-&gt;pprev)</p>
<p style="Normal" xid="1471" props="text-align:left; dom-dir:ltr">        vConnect.push_back(pindex);</p>
<p style="Normal" xid="1472" props="text-align:left; dom-dir:ltr">    reverse(vConnect.begin(), vConnect.end());</p>
<p style="Normal" xid="1473"><c></c></p>
<p style="Normal" xid="1474" props="text-align:left; dom-dir:ltr">    printf("REORGANIZE: Disconnect %i blocks; %s..%s\n", vDisconnect.size(), pfork-&gt;GetBlockHash().ToString().substr(0,20).c_str(), pindexBest-&gt;GetBlockHash().ToString().substr(0,20).c_str());</p>
<p style="Normal" xid="1475" props="text-align:left; dom-dir:ltr">    printf("REORGANIZE: Connect %i blocks; %s..%s\n", vConnect.size(), pfork-&gt;GetBlockHash().ToString().substr(0,20).c_str(), pindexNew-&gt;GetBlockHash().ToString().substr(0,20).c_str());</p>
<p style="Normal" xid="1476"><c></c></p>
<p style="Normal" xid="1477" props="text-align:left; dom-dir:ltr">    // Disconnect shorter branch</p>
<p style="Normal" xid="1478" props="text-align:left; dom-dir:ltr">    vector&lt;CTransaction&gt; vResurrect;</p>
<p style="Normal" xid="1479" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(CBlockIndex* pindex, vDisconnect)</p>
<p style="Normal" xid="1480">    {</p>
<p style="Normal" xid="1481" props="text-align:left; dom-dir:ltr">        CBlock block;</p>
<p style="Normal" xid="1482" props="text-align:left; dom-dir:ltr">        if (!block.ReadFromDisk(pindex))</p>
<p style="Normal" xid="1483" props="text-align:left; dom-dir:ltr">            return error("Reorganize() : ReadFromDisk for disconnect failed");</p>
<p style="Normal" xid="1484" props="text-align:left; dom-dir:ltr">        if (!block.DisconnectBlock(txdb, pindex))</p>
<p style="Normal" xid="1485" props="text-align:left; dom-dir:ltr">            return error("Reorganize() : DisconnectBlock %s failed", pindex-&gt;GetBlockHash().ToString().substr(0,20).c_str());</p>
<p style="Normal" xid="1486"><c></c></p>
<p style="Normal" xid="1487" props="text-align:left; dom-dir:ltr">        // Queue memory transactions to resurrect</p>
<p style="Normal" xid="1488" props="text-align:left; dom-dir:ltr">        BOOST_FOREACH(const CTransaction&amp; tx, block.vtx)</p>
<p style="Normal" xid="1489" props="text-align:left; dom-dir:ltr">            if (!tx.IsCoinBase())</p>
<p style="Normal" xid="1490" props="text-align:left; dom-dir:ltr">                vResurrect.push_back(tx);</p>
<p style="Normal" xid="1491">    }</p>
<p style="Normal" xid="1492"><c></c></p>
<p style="Normal" xid="1493" props="text-align:left; dom-dir:ltr">    // Connect longer branch</p>
<p style="Normal" xid="1494" props="text-align:left; dom-dir:ltr">    vector&lt;CTransaction&gt; vDelete;</p>
<p style="Normal" xid="1495" props="text-align:left; dom-dir:ltr">    for (unsigned int i = 0; i &lt; vConnect.size(); i++)</p>
<p style="Normal" xid="1496">    {</p>
<p style="Normal" xid="1497" props="text-align:left; dom-dir:ltr">        CBlockIndex* pindex = vConnect[i];</p>
<p style="Normal" xid="1498" props="text-align:left; dom-dir:ltr">        CBlock block;</p>
<p style="Normal" xid="1499" props="text-align:left; dom-dir:ltr">        if (!block.ReadFromDisk(pindex))</p>
<p style="Normal" xid="1500" props="text-align:left; dom-dir:ltr">            return error("Reorganize() : ReadFromDisk for connect failed");</p>
<p style="Normal" xid="1501" props="text-align:left; dom-dir:ltr">        if (!block.ConnectBlock(txdb, pindex))</p>
<p style="Normal" xid="1502">        {</p>
<p style="Normal" xid="1503" props="text-align:left; dom-dir:ltr">            // Invalid block</p>
<p style="Normal" xid="1504" props="text-align:left; dom-dir:ltr">            return error("Reorganize() : ConnectBlock %s failed", pindex-&gt;GetBlockHash().ToString().substr(0,20).c_str());</p>
<p style="Normal" xid="1505">        }</p>
<p style="Normal" xid="1506"><c></c></p>
<p style="Normal" xid="1507" props="text-align:left; dom-dir:ltr">        // Queue memory transactions to delete</p>
<p style="Normal" xid="1508" props="text-align:left; dom-dir:ltr">        BOOST_FOREACH(const CTransaction&amp; tx, block.vtx)</p>
<p style="Normal" xid="1509" props="text-align:left; dom-dir:ltr">            vDelete.push_back(tx);</p>
<p style="Normal" xid="1510">    }</p>
<p style="Normal" xid="1511" props="text-align:left; dom-dir:ltr">    if (!txdb.WriteHashBestChain(pindexNew-&gt;GetBlockHash()))</p>
<p style="Normal" xid="1512" props="text-align:left; dom-dir:ltr">        return error("Reorganize() : WriteHashBestChain failed");</p>
<p style="Normal" xid="1513"><c></c></p>
<p style="Normal" xid="1514" props="text-align:left; dom-dir:ltr">    // Make sure it's successfully written to disk before changing memory structure</p>
<p style="Normal" xid="1515" props="text-align:left; dom-dir:ltr">    if (!txdb.TxnCommit())</p>
<p style="Normal" xid="1516" props="text-align:left; dom-dir:ltr">        return error("Reorganize() : TxnCommit failed");</p>
<p style="Normal" xid="1517"><c></c></p>
<p style="Normal" xid="1518" props="text-align:left; dom-dir:ltr">    // Disconnect shorter branch</p>
<p style="Normal" xid="1519" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(CBlockIndex* pindex, vDisconnect)</p>
<p style="Normal" xid="1520" props="text-align:left; dom-dir:ltr">        if (pindex-&gt;pprev)</p>
<p style="Normal" xid="1521" props="text-align:left; dom-dir:ltr">            pindex-&gt;pprev-&gt;pnext = NULL;</p>
<p style="Normal" xid="1522"><c></c></p>
<p style="Normal" xid="1523" props="text-align:left; dom-dir:ltr">    // Connect longer branch</p>
<p style="Normal" xid="1524" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(CBlockIndex* pindex, vConnect)</p>
<p style="Normal" xid="1525" props="text-align:left; dom-dir:ltr">        if (pindex-&gt;pprev)</p>
<p style="Normal" xid="1526" props="text-align:left; dom-dir:ltr">            pindex-&gt;pprev-&gt;pnext = pindex;</p>
<p style="Normal" xid="1527"><c></c></p>
<p style="Normal" xid="1528" props="text-align:left; dom-dir:ltr">    // Resurrect memory transactions that were in the disconnected branch</p>
<p style="Normal" xid="1529" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(CTransaction&amp; tx, vResurrect)</p>
<p style="Normal" xid="1530" props="text-align:left; dom-dir:ltr">        tx.AcceptToMemoryPool(txdb, false);</p>
<p style="Normal" xid="1531"><c></c></p>
<p style="Normal" xid="1532" props="text-align:left; dom-dir:ltr">    // Delete redundant memory transactions that are in the connected branch</p>
<p style="Normal" xid="1533" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(CTransaction&amp; tx, vDelete)</p>
<p style="Normal" xid="1534" props="text-align:left; dom-dir:ltr">        mempool.remove(tx);</p>
<p style="Normal" xid="1535"><c></c></p>
<p style="Normal" xid="1536" props="text-align:left; dom-dir:ltr">    printf("REORGANIZE: done\n");</p>
<p style="Normal" xid="1537"><c></c></p>
<p style="Normal" xid="1538" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="1539">}</p>
<p style="Normal" xid="1540"><c></c></p>
<p style="Normal" xid="1541"><c></c></p>
<p style="Normal" xid="1542" props="text-align:left; dom-dir:ltr">// Called from inside SetBestChain: attaches a block to the new best chain being built</p>
<p style="Normal" xid="1543" props="text-align:left; dom-dir:ltr">bool CBlock::SetBestChainInner(CTxDB&amp; txdb, CBlockIndex *pindexNew)</p>
<p style="Normal" xid="1544">{</p>
<p style="Normal" xid="1545" props="text-align:left; dom-dir:ltr">    uint256 hash = GetHash();</p>
<p style="Normal" xid="1546"><c></c></p>
<p style="Normal" xid="1547" props="text-align:left; dom-dir:ltr">    // Adding to current best branch</p>
<p style="Normal" xid="1548" props="text-align:left; dom-dir:ltr">    if (!ConnectBlock(txdb, pindexNew) || !txdb.WriteHashBestChain(hash))</p>
<p style="Normal" xid="1549">    {</p>
<p style="Normal" xid="1550" props="text-align:left; dom-dir:ltr">        txdb.TxnAbort();</p>
<p style="Normal" xid="1551" props="text-align:left; dom-dir:ltr">        InvalidChainFound(pindexNew);</p>
<p style="Normal" xid="1552" props="text-align:left; dom-dir:ltr">        return false;</p>
<p style="Normal" xid="1553">    }</p>
<p style="Normal" xid="1554" props="text-align:left; dom-dir:ltr">    if (!txdb.TxnCommit())</p>
<p style="Normal" xid="1555" props="text-align:left; dom-dir:ltr">        return error("SetBestChain() : TxnCommit failed");</p>
<p style="Normal" xid="1556"><c></c></p>
<p style="Normal" xid="1557" props="text-align:left; dom-dir:ltr">    // Add to current best branch</p>
<p style="Normal" xid="1558" props="text-align:left; dom-dir:ltr">    pindexNew-&gt;pprev-&gt;pnext = pindexNew;</p>
<p style="Normal" xid="1559"><c></c></p>
<p style="Normal" xid="1560" props="text-align:left; dom-dir:ltr">    // Delete redundant memory transactions</p>
<p style="Normal" xid="1561" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(CTransaction&amp; tx, vtx)</p>
<p style="Normal" xid="1562" props="text-align:left; dom-dir:ltr">        mempool.remove(tx);</p>
<p style="Normal" xid="1563"><c></c></p>
<p style="Normal" xid="1564" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="1565">}</p>
<p style="Normal" xid="1566"><c></c></p>
<p style="Normal" xid="1567" props="text-align:left; dom-dir:ltr">bool CBlock::SetBestChain(CTxDB&amp; txdb, CBlockIndex* pindexNew)</p>
<p style="Normal" xid="1568">{</p>
<p style="Normal" xid="1569" props="text-align:left; dom-dir:ltr">    uint256 hash = GetHash();</p>
<p style="Normal" xid="1570"><c></c></p>
<p style="Normal" xid="1571" props="text-align:left; dom-dir:ltr">    if (!txdb.TxnBegin())</p>
<p style="Normal" xid="1572" props="text-align:left; dom-dir:ltr">        return error("SetBestChain() : TxnBegin failed");</p>
<p style="Normal" xid="1573"><c></c></p>
<p style="Normal" xid="1574" props="text-align:left; dom-dir:ltr">    if (pindexGenesisBlock == NULL &amp;&amp; hash == hashGenesisBlock)</p>
<p style="Normal" xid="1575">    {</p>
<p style="Normal" xid="1576" props="text-align:left; dom-dir:ltr">        txdb.WriteHashBestChain(hash);</p>
<p style="Normal" xid="1577" props="text-align:left; dom-dir:ltr">        if (!txdb.TxnCommit())</p>
<p style="Normal" xid="1578" props="text-align:left; dom-dir:ltr">            return error("SetBestChain() : TxnCommit failed");</p>
<p style="Normal" xid="1579" props="text-align:left; dom-dir:ltr">        pindexGenesisBlock = pindexNew;</p>
<p style="Normal" xid="1580">    }</p>
<p style="Normal" xid="1581" props="text-align:left; dom-dir:ltr">    else if (hashPrevBlock == hashBestChain)</p>
<p style="Normal" xid="1582">    {</p>
<p style="Normal" xid="1583" props="text-align:left; dom-dir:ltr">        if (!SetBestChainInner(txdb, pindexNew))</p>
<p style="Normal" xid="1584" props="text-align:left; dom-dir:ltr">            return error("SetBestChain() : SetBestChainInner failed");</p>
<p style="Normal" xid="1585">    }</p>
<p style="Normal" xid="1586" props="text-align:left; dom-dir:ltr">    else</p>
<p style="Normal" xid="1587">    {</p>
<p style="Normal" xid="1588" props="text-align:left; dom-dir:ltr">        // the first block in the new chain that will cause it to become the new best chain</p>
<p style="Normal" xid="1589" props="text-align:left; dom-dir:ltr">        CBlockIndex *pindexIntermediate = pindexNew;</p>
<p style="Normal" xid="1590"><c></c></p>
<p style="Normal" xid="1591" props="text-align:left; dom-dir:ltr">        // list of blocks that need to be connected afterwards</p>
<p style="Normal" xid="1592" props="text-align:left; dom-dir:ltr">        std::vector&lt;CBlockIndex*&gt; vpindexSecondary;</p>
<p style="Normal" xid="1593"><c></c></p>
<p style="Normal" xid="1594" props="text-align:left; dom-dir:ltr">        // Reorganize is costly in terms of db load, as it works in a single db transaction.</p>
<p style="Normal" xid="1595" props="text-align:left; dom-dir:ltr">        // Try to limit how much needs to be done inside</p>
<p style="Normal" xid="1596" props="text-align:left; dom-dir:ltr">        while (pindexIntermediate-&gt;pprev &amp;&amp; pindexIntermediate-&gt;pprev-&gt;bnChainWork &gt; pindexBest-&gt;bnChainWork)</p>
<p style="Normal" xid="1597">        {</p>
<p style="Normal" xid="1598" props="text-align:left; dom-dir:ltr">            vpindexSecondary.push_back(pindexIntermediate);</p>
<p style="Normal" xid="1599" props="text-align:left; dom-dir:ltr">            pindexIntermediate = pindexIntermediate-&gt;pprev;</p>
<p style="Normal" xid="1600">        }</p>
<p style="Normal" xid="1601"><c></c></p>
<p style="Normal" xid="1602" props="text-align:left; dom-dir:ltr">        if (!vpindexSecondary.empty())</p>
<p style="Normal" xid="1603" props="text-align:left; dom-dir:ltr">            printf("Postponing %i reconnects\n", vpindexSecondary.size());</p>
<p style="Normal" xid="1604"><c></c></p>
<p style="Normal" xid="1605" props="text-align:left; dom-dir:ltr">        // Switch to new best branch</p>
<p style="Normal" xid="1606" props="text-align:left; dom-dir:ltr">        if (!Reorganize(txdb, pindexIntermediate))</p>
<p style="Normal" xid="1607">        {</p>
<p style="Normal" xid="1608" props="text-align:left; dom-dir:ltr">            txdb.TxnAbort();</p>
<p style="Normal" xid="1609" props="text-align:left; dom-dir:ltr">            InvalidChainFound(pindexNew);</p>
<p style="Normal" xid="1610" props="text-align:left; dom-dir:ltr">            return error("SetBestChain() : Reorganize failed");</p>
<p style="Normal" xid="1611">        }</p>
<p style="Normal" xid="1612"><c></c></p>
<p style="Normal" xid="1613" props="text-align:left; dom-dir:ltr">        // Connect futher blocks</p>
<p style="Normal" xid="1614" props="text-align:left; dom-dir:ltr">        BOOST_REVERSE_FOREACH(CBlockIndex *pindex, vpindexSecondary)</p>
<p style="Normal" xid="1615">        {</p>
<p style="Normal" xid="1616" props="text-align:left; dom-dir:ltr">            CBlock block;</p>
<p style="Normal" xid="1617" props="text-align:left; dom-dir:ltr">            if (!block.ReadFromDisk(pindex))</p>
<p style="Normal" xid="1618">            {</p>
<p style="Normal" xid="1619" props="text-align:left; dom-dir:ltr">                printf("SetBestChain() : ReadFromDisk failed\n");</p>
<p style="Normal" xid="1620" props="text-align:left; dom-dir:ltr">                break;</p>
<p style="Normal" xid="1621">            }</p>
<p style="Normal" xid="1622" props="text-align:left; dom-dir:ltr">            if (!txdb.TxnBegin()) {</p>
<p style="Normal" xid="1623" props="text-align:left; dom-dir:ltr">                printf("SetBestChain() : TxnBegin 2 failed\n");</p>
<p style="Normal" xid="1624" props="text-align:left; dom-dir:ltr">                break;</p>
<p style="Normal" xid="1625">            }</p>
<p style="Normal" xid="1626" props="text-align:left; dom-dir:ltr">            // errors now are not fatal, we still did a reorganisation to a new chain in a valid way</p>
<p style="Normal" xid="1627" props="text-align:left; dom-dir:ltr">            if (!block.SetBestChainInner(txdb, pindex))</p>
<p style="Normal" xid="1628" props="text-align:left; dom-dir:ltr">                break;</p>
<p style="Normal" xid="1629">        }</p>
<p style="Normal" xid="1630">    }</p>
<p style="Normal" xid="1631"><c></c></p>
<p style="Normal" xid="1632" props="text-align:left; dom-dir:ltr">    // Update best block in wallet (so we can detect restored wallets)</p>
<p style="Normal" xid="1633" props="text-align:left; dom-dir:ltr">    bool fIsInitialDownload = IsInitialBlockDownload();</p>
<p style="Normal" xid="1634" props="text-align:left; dom-dir:ltr">    if (!fIsInitialDownload)</p>
<p style="Normal" xid="1635">    {</p>
<p style="Normal" xid="1636" props="text-align:left; dom-dir:ltr">        const CBlockLocator locator(pindexNew);</p>
<p style="Normal" xid="1637" props="text-align:left; dom-dir:ltr">        ::SetBestChain(locator);</p>
<p style="Normal" xid="1638">    }</p>
<p style="Normal" xid="1639"><c></c></p>
<p style="Normal" xid="1640" props="text-align:left; dom-dir:ltr">    // New best block</p>
<p style="Normal" xid="1641" props="text-align:left; dom-dir:ltr">    hashBestChain = hash;</p>
<p style="Normal" xid="1642" props="text-align:left; dom-dir:ltr">    pindexBest = pindexNew;</p>
<p style="Normal" xid="1643" props="text-align:left; dom-dir:ltr">    nBestHeight = pindexBest-&gt;nHeight;</p>
<p style="Normal" xid="1644" props="text-align:left; dom-dir:ltr">    bnBestChainWork = pindexNew-&gt;bnChainWork;</p>
<p style="Normal" xid="1645" props="text-align:left; dom-dir:ltr">    nTimeBestReceived = GetTime();</p>
<p style="Normal" xid="1646" props="text-align:left; dom-dir:ltr">    nTransactionsUpdated++;</p>
<p style="Normal" xid="1647" props="text-align:left; dom-dir:ltr">    printf("SetBestChain: new best=%s  height=%d  work=%s  date=%s\n",</p>
<p style="Normal" xid="1648" props="text-align:left; dom-dir:ltr">      hashBestChain.ToString().substr(0,20).c_str(), nBestHeight, bnBestChainWork.ToString().c_str(),</p>
<p style="Normal" xid="1649" props="text-align:left; dom-dir:ltr">      DateTimeStrFormat("%x %H:%M:%S", pindexBest-&gt;GetBlockTime()).c_str());</p>
<p style="Normal" xid="1650"><c></c></p>
<p style="Normal" xid="1651" props="text-align:left; dom-dir:ltr">    // Check the version of the last 100 blocks to see if we need to upgrade:</p>
<p style="Normal" xid="1652" props="text-align:left; dom-dir:ltr">    if (!fIsInitialDownload)</p>
<p style="Normal" xid="1653">    {</p>
<p style="Normal" xid="1654" props="text-align:left; dom-dir:ltr">        int nUpgraded = 0;</p>
<p style="Normal" xid="1655" props="text-align:left; dom-dir:ltr">        const CBlockIndex* pindex = pindexBest;</p>
<p style="Normal" xid="1656" props="text-align:left; dom-dir:ltr">        for (int i = 0; i &lt; 100 &amp;&amp; pindex != NULL; i++)</p>
<p style="Normal" xid="1657">        {</p>
<p style="Normal" xid="1658" props="text-align:left; dom-dir:ltr">            if (pindex-&gt;nVersion &gt; CBlock::CURRENT_VERSION)</p>
<p style="Normal" xid="1659" props="text-align:left; dom-dir:ltr">                ++nUpgraded;</p>
<p style="Normal" xid="1660" props="text-align:left; dom-dir:ltr">            pindex = pindex-&gt;pprev;</p>
<p style="Normal" xid="1661">        }</p>
<p style="Normal" xid="1662" props="text-align:left; dom-dir:ltr">        if (nUpgraded &gt; 0)</p>
<p style="Normal" xid="1663" props="text-align:left; dom-dir:ltr">            printf("SetBestChain: %d of last 100 blocks above version %d\n", nUpgraded, CBlock::CURRENT_VERSION);</p>
<p style="Normal" xid="1664" props="text-align:left; dom-dir:ltr">	//        if (nUpgraded &gt; 100/2)</p>
<p style="Normal" xid="1665" props="text-align:left; dom-dir:ltr">            // strMiscWarning is read by GetWarnings(), called by Qt and the JSON-RPC code to warn the user:</p>
<p style="Normal" xid="1666" props="text-align:left; dom-dir:ltr">	//            strMiscWarning = _("Warning: this version is obsolete, upgrade required");</p>
<p style="Normal" xid="1667">    }</p>
<p style="Normal" xid="1668"><c></c></p>
<p style="Normal" xid="1669" props="text-align:left; dom-dir:ltr">    std::string strCmd = GetArg("-blocknotify", "");</p>
<p style="Normal" xid="1670"><c></c></p>
<p style="Normal" xid="1671" props="text-align:left; dom-dir:ltr">    if (!fIsInitialDownload &amp;&amp; !strCmd.empty())</p>
<p style="Normal" xid="1672">    {</p>
<p style="Normal" xid="1673" props="text-align:left; dom-dir:ltr">        boost::replace_all(strCmd, "%s", hashBestChain.GetHex());</p>
<p style="Normal" xid="1674" props="text-align:left; dom-dir:ltr">        boost::thread t(runCommand, strCmd); // thread runs free</p>
<p style="Normal" xid="1675">    }</p>
<p style="Normal" xid="1676"><c></c></p>
<p style="Normal" xid="1677" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="1678">}</p>
<p style="Normal" xid="1679"><c></c></p>
<p style="Normal" xid="1680"><c></c></p>
<p style="Normal" xid="1681" props="text-align:left; dom-dir:ltr">bool CBlock::AddToBlockIndex(unsigned int nFile, unsigned int nBlockPos)</p>
<p style="Normal" xid="1682">{</p>
<p style="Normal" xid="1683" props="text-align:left; dom-dir:ltr">    // Check for duplicate</p>
<p style="Normal" xid="1684" props="text-align:left; dom-dir:ltr">    uint256 hash = GetHash();</p>
<p style="Normal" xid="1685" props="text-align:left; dom-dir:ltr">    if (mapBlockIndex.count(hash))</p>
<p style="Normal" xid="1686" props="text-align:left; dom-dir:ltr">        return error("AddToBlockIndex() : %s already exists", hash.ToString().substr(0,20).c_str());</p>
<p style="Normal" xid="1687"><c></c></p>
<p style="Normal" xid="1688" props="text-align:left; dom-dir:ltr">    // Construct new block index object</p>
<p style="Normal" xid="1689" props="text-align:left; dom-dir:ltr">    CBlockIndex* pindexNew = new CBlockIndex(nFile, nBlockPos, *this);</p>
<p style="Normal" xid="1690" props="text-align:left; dom-dir:ltr">    if (!pindexNew)</p>
<p style="Normal" xid="1691" props="text-align:left; dom-dir:ltr">        return error("AddToBlockIndex() : new CBlockIndex failed");</p>
<p style="Normal" xid="1692" props="text-align:left; dom-dir:ltr">    map&lt;uint256, CBlockIndex*&gt;::iterator mi = mapBlockIndex.insert(make_pair(hash, pindexNew)).first;</p>
<p style="Normal" xid="1693" props="text-align:left; dom-dir:ltr">    pindexNew-&gt;phashBlock = &amp;((*mi).first);</p>
<p style="Normal" xid="1694" props="text-align:left; dom-dir:ltr">    map&lt;uint256, CBlockIndex*&gt;::iterator miPrev = mapBlockIndex.find(hashPrevBlock);</p>
<p style="Normal" xid="1695" props="text-align:left; dom-dir:ltr">    if (miPrev != mapBlockIndex.end())</p>
<p style="Normal" xid="1696">    {</p>
<p style="Normal" xid="1697" props="text-align:left; dom-dir:ltr">        pindexNew-&gt;pprev = (*miPrev).second;</p>
<p style="Normal" xid="1698" props="text-align:left; dom-dir:ltr">        pindexNew-&gt;nHeight = pindexNew-&gt;pprev-&gt;nHeight + 1;</p>
<p style="Normal" xid="1699">    }</p>
<p style="Normal" xid="1700" props="text-align:left; dom-dir:ltr">    pindexNew-&gt;bnChainWork = (pindexNew-&gt;pprev ? pindexNew-&gt;pprev-&gt;bnChainWork : 0) + pindexNew-&gt;GetBlockWork();</p>
<p style="Normal" xid="1701"><c></c></p>
<p style="Normal" xid="1702" props="text-align:left; dom-dir:ltr">    CTxDB txdb;</p>
<p style="Normal" xid="1703" props="text-align:left; dom-dir:ltr">    if (!txdb.TxnBegin())</p>
<p style="Normal" xid="1704" props="text-align:left; dom-dir:ltr">        return false;</p>
<p style="Normal" xid="1705" props="text-align:left; dom-dir:ltr">    txdb.WriteBlockIndex(CDiskBlockIndex(pindexNew));</p>
<p style="Normal" xid="1706" props="text-align:left; dom-dir:ltr">    if (!txdb.TxnCommit())</p>
<p style="Normal" xid="1707" props="text-align:left; dom-dir:ltr">        return false;</p>
<p style="Normal" xid="1708"><c></c></p>
<p style="Normal" xid="1709" props="text-align:left; dom-dir:ltr">    // New best</p>
<p style="Normal" xid="1710" props="text-align:left; dom-dir:ltr">    if (pindexNew-&gt;bnChainWork &gt; bnBestChainWork)</p>
<p style="Normal" xid="1711" props="text-align:left; dom-dir:ltr">        if (!SetBestChain(txdb, pindexNew))</p>
<p style="Normal" xid="1712" props="text-align:left; dom-dir:ltr">            return false;</p>
<p style="Normal" xid="1713"><c></c></p>
<p style="Normal" xid="1714" props="text-align:left; dom-dir:ltr">    txdb.Close();</p>
<p style="Normal" xid="1715"><c></c></p>
<p style="Normal" xid="1716" props="text-align:left; dom-dir:ltr">    if (pindexNew == pindexBest)</p>
<p style="Normal" xid="1717">    {</p>
<p style="Normal" xid="1718" props="text-align:left; dom-dir:ltr">        // Notify UI to display prev block's coinbase if it was ours</p>
<p style="Normal" xid="1719" props="text-align:left; dom-dir:ltr">        static uint256 hashPrevBestCoinBase;</p>
<p style="Normal" xid="1720" props="text-align:left; dom-dir:ltr">        UpdatedTransaction(hashPrevBestCoinBase);</p>
<p style="Normal" xid="1721" props="text-align:left; dom-dir:ltr">        hashPrevBestCoinBase = vtx[0].GetHash();</p>
<p style="Normal" xid="1722">    }</p>
<p style="Normal" xid="1723"><c></c></p>
<p style="Normal" xid="1724" props="text-align:left; dom-dir:ltr">    uiInterface.NotifyBlocksChanged();</p>
<p style="Normal" xid="1725" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="1726">}</p>
<p style="Normal" xid="1727"><c></c></p>
<p style="Normal" xid="1728"><c></c></p>
<p style="Normal" xid="1729"><c></c></p>
<p style="Normal" xid="1730"><c></c></p>
<p style="Normal" xid="1731" props="text-align:left; dom-dir:ltr">bool CBlock::CheckBlock() const</p>
<p style="Normal" xid="1732">{</p>
<p style="Normal" xid="1733" props="text-align:left; dom-dir:ltr">    // These are checks that are independent of context</p>
<p style="Normal" xid="1734" props="text-align:left; dom-dir:ltr">    // that can be verified before saving an orphan block.</p>
<p style="Normal" xid="1735"><c></c></p>
<p style="Normal" xid="1736" props="text-align:left; dom-dir:ltr">    // Size limits</p>
<p style="Normal" xid="1737" props="text-align:left; dom-dir:ltr">    if (vtx.empty() || vtx.size() &gt; MAX_BLOCK_SIZE || ::GetSerializeSize(*this, SER_NETWORK, PROTOCOL_VERSION) &gt; MAX_BLOCK_SIZE)</p>
<p style="Normal" xid="1738" props="text-align:left; dom-dir:ltr">        return DoS(100, error("CheckBlock() : size limits failed"));</p>
<p style="Normal" xid="1739"><c></c></p>
<p style="Normal" xid="1740" props="text-align:left; dom-dir:ltr">    // Check proof of work matches claimed amount</p>
<p style="Normal" xid="1741" props="text-align:left; dom-dir:ltr">    if (!CheckProofOfWork(GetPoWHash(), nBits))</p>
<p style="Normal" xid="1742" props="text-align:left; dom-dir:ltr">        return DoS(50, error("CheckBlock() : proof of work failed"));</p>
<p style="Normal" xid="1743"><c></c></p>
<p style="Normal" xid="1744" props="text-align:left; dom-dir:ltr">    // Check timestamp</p>
<p style="Normal" xid="1745" props="text-align:left; dom-dir:ltr">    if (GetBlockTime() &gt; GetAdjustedTime() + 2 * 60 * 60)</p>
<p style="Normal" xid="1746" props="text-align:left; dom-dir:ltr">        return error("CheckBlock() : block timestamp too far in the future");</p>
<p style="Normal" xid="1747"><c></c></p>
<p style="Normal" xid="1748" props="text-align:left; dom-dir:ltr">    // First transaction must be coinbase, the rest must not be</p>
<p style="Normal" xid="1749" props="text-align:left; dom-dir:ltr">    if (vtx.empty() || !vtx[0].IsCoinBase())</p>
<p style="Normal" xid="1750" props="text-align:left; dom-dir:ltr">        return DoS(100, error("CheckBlock() : first tx is not coinbase"));</p>
<p style="Normal" xid="1751" props="text-align:left; dom-dir:ltr">    for (unsigned int i = 1; i &lt; vtx.size(); i++)</p>
<p style="Normal" xid="1752" props="text-align:left; dom-dir:ltr">        if (vtx[i].IsCoinBase())</p>
<p style="Normal" xid="1753" props="text-align:left; dom-dir:ltr">            return DoS(100, error("CheckBlock() : more than one coinbase"));</p>
<p style="Normal" xid="1754"><c></c></p>
<p style="Normal" xid="1755" props="text-align:left; dom-dir:ltr">    // Check transactions</p>
<p style="Normal" xid="1756" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(const CTransaction&amp; tx, vtx)</p>
<p style="Normal" xid="1757" props="text-align:left; dom-dir:ltr">        if (!tx.CheckTransaction())</p>
<p style="Normal" xid="1758" props="text-align:left; dom-dir:ltr">            return DoS(tx.nDoS, error("CheckBlock() : CheckTransaction failed"));</p>
<p style="Normal" xid="1759"><c></c></p>
<p style="Normal" xid="1760" props="text-align:left; dom-dir:ltr">    // Check for duplicate txids. This is caught by ConnectInputs(),</p>
<p style="Normal" xid="1761" props="text-align:left; dom-dir:ltr">    // but catching it earlier avoids a potential DoS attack:</p>
<p style="Normal" xid="1762" props="text-align:left; dom-dir:ltr">    set&lt;uint256&gt; uniqueTx;</p>
<p style="Normal" xid="1763" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(const CTransaction&amp; tx, vtx)</p>
<p style="Normal" xid="1764">    {</p>
<p style="Normal" xid="1765" props="text-align:left; dom-dir:ltr">        uniqueTx.insert(tx.GetHash());</p>
<p style="Normal" xid="1766">    }</p>
<p style="Normal" xid="1767" props="text-align:left; dom-dir:ltr">    if (uniqueTx.size() != vtx.size())</p>
<p style="Normal" xid="1768" props="text-align:left; dom-dir:ltr">        return DoS(100, error("CheckBlock() : duplicate transaction"));</p>
<p style="Normal" xid="1769"><c></c></p>
<p style="Normal" xid="1770" props="text-align:left; dom-dir:ltr">    unsigned int nSigOps = 0;</p>
<p style="Normal" xid="1771" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(const CTransaction&amp; tx, vtx)</p>
<p style="Normal" xid="1772">    {</p>
<p style="Normal" xid="1773" props="text-align:left; dom-dir:ltr">        nSigOps += tx.GetLegacySigOpCount();</p>
<p style="Normal" xid="1774">    }</p>
<p style="Normal" xid="1775" props="text-align:left; dom-dir:ltr">    if (nSigOps &gt; MAX_BLOCK_SIGOPS)</p>
<p style="Normal" xid="1776" props="text-align:left; dom-dir:ltr">        return DoS(100, error("CheckBlock() : out-of-bounds SigOpCount"));</p>
<p style="Normal" xid="1777"><c></c></p>
<p style="Normal" xid="1778" props="text-align:left; dom-dir:ltr">    // Check merkleroot</p>
<p style="Normal" xid="1779" props="text-align:left; dom-dir:ltr">    if (hashMerkleRoot != BuildMerkleTree())</p>
<p style="Normal" xid="1780" props="text-align:left; dom-dir:ltr">        return DoS(100, error("CheckBlock() : hashMerkleRoot mismatch"));</p>
<p style="Normal" xid="1781"><c></c></p>
<p style="Normal" xid="1782" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="1783">}</p>
<p style="Normal" xid="1784"><c></c></p>
<p style="Normal" xid="1785" props="text-align:left; dom-dir:ltr">bool CBlock::AcceptBlock()</p>
<p style="Normal" xid="1786">{</p>
<p style="Normal" xid="1787" props="text-align:left; dom-dir:ltr">    // Check for duplicate</p>
<p style="Normal" xid="1788" props="text-align:left; dom-dir:ltr">    uint256 hash = GetHash();</p>
<p style="Normal" xid="1789" props="text-align:left; dom-dir:ltr">    if (mapBlockIndex.count(hash))</p>
<p style="Normal" xid="1790" props="text-align:left; dom-dir:ltr">        return error("AcceptBlock() : block already in mapBlockIndex");</p>
<p style="Normal" xid="1791"><c></c></p>
<p style="Normal" xid="1792" props="text-align:left; dom-dir:ltr">    // Get prev block index</p>
<p style="Normal" xid="1793" props="text-align:left; dom-dir:ltr">    map&lt;uint256, CBlockIndex*&gt;::iterator mi = mapBlockIndex.find(hashPrevBlock);</p>
<p style="Normal" xid="1794" props="text-align:left; dom-dir:ltr">    if (mi == mapBlockIndex.end())</p>
<p style="Normal" xid="1795" props="text-align:left; dom-dir:ltr">        return DoS(10, error("AcceptBlock() : prev block not found"));</p>
<p style="Normal" xid="1796" props="text-align:left; dom-dir:ltr">    CBlockIndex* pindexPrev = (*mi).second;</p>
<p style="Normal" xid="1797" props="text-align:left; dom-dir:ltr">    int nHeight = pindexPrev-&gt;nHeight+1;</p>
<p style="Normal" xid="1798"><c></c></p>
<p style="Normal" xid="1799" props="text-align:left; dom-dir:ltr">    // Check proof of work</p>
<p style="Normal" xid="1800" props="text-align:left; dom-dir:ltr">    if (nBits != GetNextWorkRequired(pindexPrev, this))</p>
<p style="Normal" xid="1801" props="text-align:left; dom-dir:ltr">        return DoS(100, error("AcceptBlock() : incorrect proof of work"));</p>
<p style="Normal" xid="1802"><c></c></p>
<p style="Normal" xid="1803" props="text-align:left; dom-dir:ltr">    // Check timestamp against prev</p>
<p style="Normal" xid="1804" props="text-align:left; dom-dir:ltr">    if (GetBlockTime() &lt;= pindexPrev-&gt;GetMedianTimePast())</p>
<p style="Normal" xid="1805" props="text-align:left; dom-dir:ltr">        return error("AcceptBlock() : block's timestamp is too early");</p>
<p style="Normal" xid="1806"><c></c></p>
<p style="Normal" xid="1807" props="text-align:left; dom-dir:ltr">    // Check that all transactions are finalized</p>
<p style="Normal" xid="1808" props="text-align:left; dom-dir:ltr">    BOOST_FOREACH(const CTransaction&amp; tx, vtx)</p>
<p style="Normal" xid="1809" props="text-align:left; dom-dir:ltr">        if (!tx.IsFinal(nHeight, GetBlockTime()))</p>
<p style="Normal" xid="1810" props="text-align:left; dom-dir:ltr">            return DoS(10, error("AcceptBlock() : contains a non-final transaction"));</p>
<p style="Normal" xid="1811"><c></c></p>
<p style="Normal" xid="1812" props="text-align:left; dom-dir:ltr">    // Check that the block chain matches the known block chain up to a checkpoint</p>
<p style="Normal" xid="1813" props="text-align:left; dom-dir:ltr">    if (!Checkpoints::CheckBlock(nHeight, hash))</p>
<p style="Normal" xid="1814" props="text-align:left; dom-dir:ltr">        return DoS(100, error("AcceptBlock() : rejected by checkpoint lockin at %d", nHeight));</p>
<p style="Normal" xid="1815"><c></c></p>
<p style="Normal" xid="1816" props="text-align:left; dom-dir:ltr">    // Write block to history file</p>
<p style="Normal" xid="1817" props="text-align:left; dom-dir:ltr">    if (!CheckDiskSpace(::GetSerializeSize(*this, SER_DISK, CLIENT_VERSION)))</p>
<p style="Normal" xid="1818" props="text-align:left; dom-dir:ltr">        return error("AcceptBlock() : out of disk space");</p>
<p style="Normal" xid="1819" props="text-align:left; dom-dir:ltr">    unsigned int nFile = -1;</p>
<p style="Normal" xid="1820" props="text-align:left; dom-dir:ltr">    unsigned int nBlockPos = 0;</p>
<p style="Normal" xid="1821" props="text-align:left; dom-dir:ltr">    if (!WriteToDisk(nFile, nBlockPos))</p>
<p style="Normal" xid="1822" props="text-align:left; dom-dir:ltr">        return error("AcceptBlock() : WriteToDisk failed");</p>
<p style="Normal" xid="1823" props="text-align:left; dom-dir:ltr">    if (!AddToBlockIndex(nFile, nBlockPos))</p>
<p style="Normal" xid="1824" props="text-align:left; dom-dir:ltr">        return error("AcceptBlock() : AddToBlockIndex failed");</p>
<p style="Normal" xid="1825"><c></c></p>
<p style="Normal" xid="1826" props="text-align:left; dom-dir:ltr">    // Relay inventory, but don't relay old inventory during initial block download</p>
<p style="Normal" xid="1827" props="text-align:left; dom-dir:ltr">    int nBlockEstimate = Checkpoints::GetTotalBlocksEstimate();</p>
<p style="Normal" xid="1828" props="text-align:left; dom-dir:ltr">    if (hashBestChain == hash)</p>
<p style="Normal" xid="1829">    {</p>
<p style="Normal" xid="1830" props="text-align:left; dom-dir:ltr">        LOCK(cs_vNodes);</p>
<p style="Normal" xid="1831" props="text-align:left; dom-dir:ltr">        BOOST_FOREACH(CNode* pnode, vNodes)</p>
<p style="Normal" xid="1832" props="text-align:left; dom-dir:ltr">            if (nBestHeight &gt; (pnode-&gt;nStartingHeight != -1 ? pnode-&gt;nStartingHeight - 2000 : nBlockEstimate))</p>
<p style="Normal" xid="1833" props="text-align:left; dom-dir:ltr">                pnode-&gt;PushInventory(CInv(MSG_BLOCK, hash));</p>
<p style="Normal" xid="1834">    }</p>
<p style="Normal" xid="1835"><c></c></p>
<p style="Normal" xid="1836" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="1837">}</p>
<p style="Normal" xid="1838"><c></c></p>
<p style="Normal" xid="1839" props="text-align:left; dom-dir:ltr">bool ProcessBlock(CNode* pfrom, CBlock* pblock)</p>
<p style="Normal" xid="1840">{</p>
<p style="Normal" xid="1841" props="text-align:left; dom-dir:ltr">    // Check for duplicate</p>
<p style="Normal" xid="1842" props="text-align:left; dom-dir:ltr">    uint256 hash = pblock-&gt;GetHash();</p>
<p style="Normal" xid="1843" props="text-align:left; dom-dir:ltr">    if (mapBlockIndex.count(hash))</p>
<p style="Normal" xid="1844" props="text-align:left; dom-dir:ltr">        return error("ProcessBlock() : already have block %d %s", mapBlockIndex[hash]-&gt;nHeight, hash.ToString().substr(0,20).c_str());</p>
<p style="Normal" xid="1845" props="text-align:left; dom-dir:ltr">    if (mapOrphanBlocks.count(hash))</p>
<p style="Normal" xid="1846" props="text-align:left; dom-dir:ltr">        return error("ProcessBlock() : already have block (orphan) %s", hash.ToString().substr(0,20).c_str());</p>
<p style="Normal" xid="1847"><c></c></p>
<p style="Normal" xid="1848" props="text-align:left; dom-dir:ltr">    // Preliminary checks</p>
<p style="Normal" xid="1849" props="text-align:left; dom-dir:ltr">    if (!pblock-&gt;CheckBlock())</p>
<p style="Normal" xid="1850" props="text-align:left; dom-dir:ltr">        return error("ProcessBlock() : CheckBlock FAILED");</p>
<p style="Normal" xid="1851"><c></c></p>
<p style="Normal" xid="1852" props="text-align:left; dom-dir:ltr">    CBlockIndex* pcheckpoint = Checkpoints::GetLastCheckpoint(mapBlockIndex);</p>
<p style="Normal" xid="1853" props="text-align:left; dom-dir:ltr">    if (pcheckpoint &amp;&amp; pblock-&gt;hashPrevBlock != hashBestChain)</p>
<p style="Normal" xid="1854">    {</p>
<p style="Normal" xid="1855" props="text-align:left; dom-dir:ltr">        // Extra checks to prevent "fill up memory by spamming with bogus blocks"</p>
<p style="Normal" xid="1856" props="text-align:left; dom-dir:ltr">        int64 deltaTime = pblock-&gt;GetBlockTime() - pcheckpoint-&gt;nTime;</p>
<p style="Normal" xid="1857" props="text-align:left; dom-dir:ltr">        if (deltaTime &lt; 0)</p>
<p style="Normal" xid="1858">        {</p>
<p style="Normal" xid="1859" props="text-align:left; dom-dir:ltr">            if (pfrom)</p>
<p style="Normal" xid="1860" props="text-align:left; dom-dir:ltr">                pfrom-&gt;Misbehaving(100);</p>
<p style="Normal" xid="1861" props="text-align:left; dom-dir:ltr">            return error("ProcessBlock() : block with timestamp before last checkpoint");</p>
<p style="Normal" xid="1862">        }</p>
<p style="Normal" xid="1863" props="text-align:left; dom-dir:ltr">        CBigNum bnNewBlock;</p>
<p style="Normal" xid="1864" props="text-align:left; dom-dir:ltr">        bnNewBlock.SetCompact(pblock-&gt;nBits);</p>
<p style="Normal" xid="1865" props="text-align:left; dom-dir:ltr">        CBigNum bnRequired;</p>
<p style="Normal" xid="1866" props="text-align:left; dom-dir:ltr">        bnRequired.SetCompact(ComputeMinWork(pcheckpoint-&gt;nBits, deltaTime));</p>
<p style="Normal" xid="1867" props="text-align:left; dom-dir:ltr">        if (bnNewBlock &gt; bnRequired)</p>
<p style="Normal" xid="1868">        {</p>
<p style="Normal" xid="1869" props="text-align:left; dom-dir:ltr">            if (pfrom)</p>
<p style="Normal" xid="1870" props="text-align:left; dom-dir:ltr">                pfrom-&gt;Misbehaving(100);</p>
<p style="Normal" xid="1871" props="text-align:left; dom-dir:ltr">            return error("ProcessBlock() : block with too little proof-of-work");</p>
<p style="Normal" xid="1872">        }</p>
<p style="Normal" xid="1873">    }</p>
<p style="Normal" xid="1874"><c></c></p>
<p style="Normal" xid="1875"><c></c></p>
<p style="Normal" xid="1876" props="text-align:left; dom-dir:ltr">    // If don't already have its previous block, shunt it off to holding area until we get it</p>
<p style="Normal" xid="1877" props="text-align:left; dom-dir:ltr">    if (!mapBlockIndex.count(pblock-&gt;hashPrevBlock))</p>
<p style="Normal" xid="1878">    {</p>
<p style="Normal" xid="1879" props="text-align:left; dom-dir:ltr">        printf("ProcessBlock: ORPHAN BLOCK, prev=%s\n", pblock-&gt;hashPrevBlock.ToString().substr(0,20).c_str());</p>
<p style="Normal" xid="1880" props="text-align:left; dom-dir:ltr">        CBlock* pblock2 = new CBlock(*pblock);</p>
<p style="Normal" xid="1881" props="text-align:left; dom-dir:ltr">        mapOrphanBlocks.insert(make_pair(hash, pblock2));</p>
<p style="Normal" xid="1882" props="text-align:left; dom-dir:ltr">        mapOrphanBlocksByPrev.insert(make_pair(pblock2-&gt;hashPrevBlock, pblock2));</p>
<p style="Normal" xid="1883"><c></c></p>
<p style="Normal" xid="1884" props="text-align:left; dom-dir:ltr">        // Ask this guy to fill in what we're missing</p>
<p style="Normal" xid="1885" props="text-align:left; dom-dir:ltr">        if (pfrom)</p>
<p style="Normal" xid="1886" props="text-align:left; dom-dir:ltr">            pfrom-&gt;PushGetBlocks(pindexBest, GetOrphanRoot(pblock2));</p>
<p style="Normal" xid="1887" props="text-align:left; dom-dir:ltr">        return true;</p>
<p style="Normal" xid="1888">    }</p>
<p style="Normal" xid="1889"><c></c></p>
<p style="Normal" xid="1890" props="text-align:left; dom-dir:ltr">    // Store to disk</p>
<p style="Normal" xid="1891" props="text-align:left; dom-dir:ltr">    if (!pblock-&gt;AcceptBlock())</p>
<p style="Normal" xid="1892" props="text-align:left; dom-dir:ltr">        return error("ProcessBlock() : AcceptBlock FAILED");</p>
<p style="Normal" xid="1893"><c></c></p>
<p style="Normal" xid="1894" props="text-align:left; dom-dir:ltr">    // Recursively process any orphan blocks that depended on this one</p>
<p style="Normal" xid="1895" props="text-align:left; dom-dir:ltr">    vector&lt;uint256&gt; vWorkQueue;</p>
<p style="Normal" xid="1896" props="text-align:left; dom-dir:ltr">    vWorkQueue.push_back(hash);</p>
<p style="Normal" xid="1897" props="text-align:left; dom-dir:ltr">    for (unsigned int i = 0; i &lt; vWorkQueue.size(); i++)</p>
<p style="Normal" xid="1898">    {</p>
<p style="Normal" xid="1899" props="text-align:left; dom-dir:ltr">        uint256 hashPrev = vWorkQueue[i];</p>
<p style="Normal" xid="1900" props="text-align:left; dom-dir:ltr">        for (multimap&lt;uint256, CBlock*&gt;::iterator mi = mapOrphanBlocksByPrev.lower_bound(hashPrev);</p>
<p style="Normal" xid="1901" props="text-align:left; dom-dir:ltr">             mi != mapOrphanBlocksByPrev.upper_bound(hashPrev);</p>
<p style="Normal" xid="1902" props="text-align:left; dom-dir:ltr">             ++mi)</p>
<p style="Normal" xid="1903">        {</p>
<p style="Normal" xid="1904" props="text-align:left; dom-dir:ltr">            CBlock* pblockOrphan = (*mi).second;</p>
<p style="Normal" xid="1905" props="text-align:left; dom-dir:ltr">            if (pblockOrphan-&gt;AcceptBlock())</p>
<p style="Normal" xid="1906" props="text-align:left; dom-dir:ltr">                vWorkQueue.push_back(pblockOrphan-&gt;GetHash());</p>
<p style="Normal" xid="1907" props="text-align:left; dom-dir:ltr">            mapOrphanBlocks.erase(pblockOrphan-&gt;GetHash());</p>
<p style="Normal" xid="1908" props="text-align:left; dom-dir:ltr">            delete pblockOrphan;</p>
<p style="Normal" xid="1909">        }</p>
<p style="Normal" xid="1910" props="text-align:left; dom-dir:ltr">        mapOrphanBlocksByPrev.erase(hashPrev);</p>
<p style="Normal" xid="1911">    }</p>
<p style="Normal" xid="1912"><c></c></p>
<p style="Normal" xid="1913" props="text-align:left; dom-dir:ltr">    printf("ProcessBlock: ACCEPTED\n");</p>
<p style="Normal" xid="1914" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="1915">}</p>
<p style="Normal" xid="1916"><c></c></p>
<p style="Normal" xid="1917"><c></c></p>
<p style="Normal" xid="1918"><c></c></p>
<p style="Normal" xid="1919"><c></c></p>
<p style="Normal" xid="1920"><c></c></p>
<p style="Normal" xid="1921"><c></c></p>
<p style="Normal" xid="1922"><c></c></p>
<p style="Normal" xid="1923"><c></c></p>
<p style="Normal" xid="1924" props="text-align:left; dom-dir:ltr">bool CheckDiskSpace(uint64 nAdditionalBytes)</p>
<p style="Normal" xid="1925">{</p>
<p style="Normal" xid="1926" props="text-align:left; dom-dir:ltr">    uint64 nFreeBytesAvailable = filesystem::space(GetDataDir()).available;</p>
<p style="Normal" xid="1927"><c></c></p>
<p style="Normal" xid="1928" props="text-align:left; dom-dir:ltr">    // Check for nMinDiskSpace bytes (currently 50MB)</p>
<p style="Normal" xid="1929" props="text-align:left; dom-dir:ltr">    if (nFreeBytesAvailable &lt; nMinDiskSpace + nAdditionalBytes)</p>
<p style="Normal" xid="1930">    {</p>
<p style="Normal" xid="1931" props="text-align:left; dom-dir:ltr">        fShutdown = true;</p>
<p style="Normal" xid="1932" props="text-align:left; dom-dir:ltr">        string strMessage = _("Warning: Disk space is low");</p>
<p style="Normal" xid="1933" props="text-align:left; dom-dir:ltr">        strMiscWarning = strMessage;</p>
<p style="Normal" xid="1934" props="text-align:left; dom-dir:ltr">        printf("*** %s\n", strMessage.c_str());</p>
<p style="Normal" xid="1935" props="text-align:left; dom-dir:ltr">        uiInterface.ThreadSafeMessageBox(strMessage, "FlightCoin", CClientUIInterface::OK | CClientUIInterface::ICON_EXCLAMATION | CClientUIInterface::MODAL);</p>
<p style="Normal" xid="1936" props="text-align:left; dom-dir:ltr">        StartShutdown();</p>
<p style="Normal" xid="1937" props="text-align:left; dom-dir:ltr">        return false;</p>
<p style="Normal" xid="1938">    }</p>
<p style="Normal" xid="1939" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="1940">}</p>
<p style="Normal" xid="1941"><c></c></p>
<p style="Normal" xid="1942" props="text-align:left; dom-dir:ltr">FILE* OpenBlockFile(unsigned int nFile, unsigned int nBlockPos, const char* pszMode)</p>
<p style="Normal" xid="1943">{</p>
<p style="Normal" xid="1944" props="text-align:left; dom-dir:ltr">    if ((nFile &lt; 1) || (nFile == (unsigned int) -1))</p>
<p style="Normal" xid="1945" props="text-align:left; dom-dir:ltr">        return NULL;</p>
<p style="Normal" xid="1946" props="text-align:left; dom-dir:ltr">    FILE* file = fopen((GetDataDir() / strprintf("blk%04d.dat", nFile)).string().c_str(), pszMode);</p>
<p style="Normal" xid="1947" props="text-align:left; dom-dir:ltr">    if (!file)</p>
<p style="Normal" xid="1948" props="text-align:left; dom-dir:ltr">        return NULL;</p>
<p style="Normal" xid="1949" props="text-align:left; dom-dir:ltr">    if (nBlockPos != 0 &amp;&amp; !strchr(pszMode, 'a') &amp;&amp; !strchr(pszMode, 'w'))</p>
<p style="Normal" xid="1950">    {</p>
<p style="Normal" xid="1951" props="text-align:left; dom-dir:ltr">        if (fseek(file, nBlockPos, SEEK_SET) != 0)</p>
<p style="Normal" xid="1952">        {</p>
<p style="Normal" xid="1953" props="text-align:left; dom-dir:ltr">            fclose(file);</p>
<p style="Normal" xid="1954" props="text-align:left; dom-dir:ltr">            return NULL;</p>
<p style="Normal" xid="1955">        }</p>
<p style="Normal" xid="1956">    }</p>
<p style="Normal" xid="1957" props="text-align:left; dom-dir:ltr">    return file;</p>
<p style="Normal" xid="1958">}</p>
<p style="Normal" xid="1959"><c></c></p>
<p style="Normal" xid="1960" props="text-align:left; dom-dir:ltr">static unsigned int nCurrentBlockFile = 1;</p>
<p style="Normal" xid="1961"><c></c></p>
<p style="Normal" xid="1962" props="text-align:left; dom-dir:ltr">FILE* AppendBlockFile(unsigned int&amp; nFileRet)</p>
<p style="Normal" xid="1963">{</p>
<p style="Normal" xid="1964" props="text-align:left; dom-dir:ltr">    nFileRet = 0;</p>
<p style="Normal" xid="1965" props="text-align:left; dom-dir:ltr">    loop</p>
<p style="Normal" xid="1966">    {</p>
<p style="Normal" xid="1967" props="text-align:left; dom-dir:ltr">        FILE* file = OpenBlockFile(nCurrentBlockFile, 0, "ab");</p>
<p style="Normal" xid="1968" props="text-align:left; dom-dir:ltr">        if (!file)</p>
<p style="Normal" xid="1969" props="text-align:left; dom-dir:ltr">            return NULL;</p>
<p style="Normal" xid="1970" props="text-align:left; dom-dir:ltr">        if (fseek(file, 0, SEEK_END) != 0)</p>
<p style="Normal" xid="1971" props="text-align:left; dom-dir:ltr">            return NULL;</p>
<p style="Normal" xid="1972" props="text-align:left; dom-dir:ltr">        // FAT32 filesize max 4GB, fseek and ftell max 2GB, so we must stay under 2GB</p>
<p style="Normal" xid="1973" props="text-align:left; dom-dir:ltr">        if (ftell(file) &lt; 0x7F000000 - MAX_SIZE)</p>
<p style="Normal" xid="1974">        {</p>
<p style="Normal" xid="1975" props="text-align:left; dom-dir:ltr">            nFileRet = nCurrentBlockFile;</p>
<p style="Normal" xid="1976" props="text-align:left; dom-dir:ltr">            return file;</p>
<p style="Normal" xid="1977">        }</p>
<p style="Normal" xid="1978" props="text-align:left; dom-dir:ltr">        fclose(file);</p>
<p style="Normal" xid="1979" props="text-align:left; dom-dir:ltr">        nCurrentBlockFile++;</p>
<p style="Normal" xid="1980">    }</p>
<p style="Normal" xid="1981">}</p>
<p style="Normal" xid="1982"><c></c></p>
<p style="Normal" xid="1983" props="text-align:left; dom-dir:ltr">bool LoadBlockIndex(bool fAllowNew)</p>
<p style="Normal" xid="1984">{</p>
<p style="Normal" xid="1985" props="text-align:left; dom-dir:ltr">    if (fTestNet)</p>
<p style="Normal" xid="1986">    {</p>
<p style="Normal" xid="1987" props="text-align:left; dom-dir:ltr">        pchMessageStart[0] = 0xfb;</p>
<p style="Normal" xid="1988" props="text-align:left; dom-dir:ltr">        pchMessageStart[1] = 0xc0;</p>
<p style="Normal" xid="1989" props="text-align:left; dom-dir:ltr">        pchMessageStart[2] = 0xb8;</p>
<p style="Normal" xid="1990" props="text-align:left; dom-dir:ltr">        pchMessageStart[3] = 0xdb;</p>
<p style="Normal" xid="1991" props="text-align:left; dom-dir:ltr">        hashGenesisBlock = uint256("0xa50faf35e1dddf4a076a907fbcef6d9d1595390cdb1c818a35dae53b67ad0aa8");</p>
<p style="Normal" xid="1992">    }</p>
<p style="Normal" xid="1993"><c></c></p>
<p style="Normal" xid="1994">    //</p>
<p style="Normal" xid="1995" props="text-align:left; dom-dir:ltr">    // Load block index</p>
<p style="Normal" xid="1996">    //</p>
<p style="Normal" xid="1997" props="text-align:left; dom-dir:ltr">    CTxDB txdb("cr");</p>
<p style="Normal" xid="1998" props="text-align:left; dom-dir:ltr">    if (!txdb.LoadBlockIndex())</p>
<p style="Normal" xid="1999" props="text-align:left; dom-dir:ltr">        return false;</p>
<p style="Normal" xid="2000" props="text-align:left; dom-dir:ltr">    txdb.Close();</p>
<p style="Normal" xid="2001"><c></c></p>
<p style="Normal" xid="2002">    //</p>
<p style="Normal" xid="2003" props="text-align:left; dom-dir:ltr">    // Init with genesis block</p>
<p style="Normal" xid="2004">    //</p>
<p style="Normal" xid="2005" props="text-align:left; dom-dir:ltr">    if (mapBlockIndex.empty())</p>
<p style="Normal" xid="2006">    {</p>
<p style="Normal" xid="2007" props="text-align:left; dom-dir:ltr">        if (!fAllowNew)</p>
<p style="Normal" xid="2008" props="text-align:left; dom-dir:ltr">            return false;</p>
<p style="Normal" xid="2009">    </p>
<p style="Normal" xid="2010" props="text-align:left; dom-dir:ltr">	// Genesis block:</p>
<p style="Normal" xid="2011" props="text-align:left; dom-dir:ltr">	// block.nTime = 1394520462 </p>
<p style="Normal" xid="2012" props="text-align:left; dom-dir:ltr">	// block.nNonce = 2085386442 </p>
<p style="Normal" xid="2013" props="text-align:left; dom-dir:ltr">	// block.GetHash = 384b060671f4a93948e9c168216dadb0ca2fbc54aa11c86b0345b6af1c59b2f5</p>
<p style="Normal" xid="2014" props="text-align:left; dom-dir:ltr">	// CBlock(hash=384b060671f4a93948e9, PoW=00000951e146b0026411, ver=1,</p>
<p style="Normal" xid="2015" props="text-align:left; dom-dir:ltr">	//  hashPrevBlock=00000000000000000000, hashMerkleRoot=5a2e19825b,</p>
<p style="Normal" xid="2016" props="text-align:left; dom-dir:ltr">	//  nTime=1394520462, nBits=1e0ffff0, nNonce=2085386442, vtx=1)</p>
<p style="Normal" xid="2017" props="text-align:left; dom-dir:ltr">	// CTransaction(hash=5a2e19825b, ver=1, vin.size=1, vout.size=1, nLockTime=0)</p>
<p style="Normal" xid="2018" props="text-align:left; dom-dir:ltr">	// CTxIn(COutPoint(0000000000, -1), coinbase 04ffff001d010441746f646f3a207265706c616365207769746820736f6d657468696e67207468617420656e7375726573206e6f207072656d696e696e6720746f6f6b20706c616365)</p>
<p style="Normal" xid="2019" props="text-align:left; dom-dir:ltr">	// CTxOut(error)</p>
<p style="Normal" xid="2020" props="text-align:left; dom-dir:ltr">	// vMerkleTree: 5a2e19825b</p>
<p style="Normal" xid="2021">        </p>
<p style="Normal" xid="2022" props="text-align:left; dom-dir:ltr">        // Genesis block</p>
<p style="Normal" xid="2023" props="text-align:left; dom-dir:ltr">        const char* pszTimestamp = "todo: replace with something that ensures no premining took place";</p>
<p style="Normal" xid="2024" props="text-align:left; dom-dir:ltr">        CTransaction txNew;</p>
<p style="Normal" xid="2025" props="text-align:left; dom-dir:ltr">        txNew.vin.resize(1);</p>
<p style="Normal" xid="2026" props="text-align:left; dom-dir:ltr">        txNew.vout.resize(1);</p>
<p style="Normal" xid="2027" props="text-align:left; dom-dir:ltr">        txNew.vin[0].scriptSig = CScript() &lt;&lt; 486604799 &lt;&lt; CBigNum(4) &lt;&lt; vector&lt;unsigned char&gt;((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));</p>
<p style="Normal" xid="2028" props="text-align:left; dom-dir:ltr">        txNew.vout[0].nValue = 0;</p>
<p style="Normal" xid="2029" props="text-align:left; dom-dir:ltr">        txNew.vout[0].scriptPubKey = CScript() &lt;&lt; 0x0 &lt;&lt; OP_CHECKSIG; // a privkey for that 'vanity' pubkey would be interesting ;)</p>
<p style="Normal" xid="2030" props="text-align:left; dom-dir:ltr">        CBlock block;</p>
<p style="Normal" xid="2031" props="text-align:left; dom-dir:ltr">        block.vtx.push_back(txNew);</p>
<p style="Normal" xid="2032" props="text-align:left; dom-dir:ltr">        block.hashPrevBlock = 0;</p>
<p style="Normal" xid="2033" props="text-align:left; dom-dir:ltr">        block.hashMerkleRoot = block.BuildMerkleTree();</p>
<p style="Normal" xid="2034" props="text-align:left; dom-dir:ltr">        block.nVersion = 1;</p>
<p style="Normal" xid="2035" props="text-align:left; dom-dir:ltr">        block.nTime    = 1394520462;</p>
<p style="Normal" xid="2036" props="text-align:left; dom-dir:ltr">        block.nBits    = 0x1e0ffff0;</p>
<p style="Normal" xid="2037" props="text-align:left; dom-dir:ltr">        block.nNonce   = 2085386442;</p>
<p style="Normal" xid="2038"><c></c></p>
<p style="Normal" xid="2039" props="text-align:left; dom-dir:ltr">        if (fTestNet)</p>
<p style="Normal" xid="2040">        {</p>
<p style="Normal" xid="2041" props="text-align:left; dom-dir:ltr">            block.nTime    = 1394520462;</p>
<p style="Normal" xid="2042" props="text-align:left; dom-dir:ltr">            block.nNonce   = 386402991;</p>
<p style="Normal" xid="2043">        }</p>
<p style="Normal" xid="2044"><c></c></p>
<p style="Normal" xid="2045" props="text-align:left; dom-dir:ltr">        //// debug print</p>
<p style="Normal" xid="2046" props="text-align:left; dom-dir:ltr">        printf("%s\n", block.GetHash().ToString().c_str());</p>
<p style="Normal" xid="2047" props="text-align:left; dom-dir:ltr">        printf("%s\n", hashGenesisBlock.ToString().c_str());</p>
<p style="Normal" xid="2048" props="text-align:left; dom-dir:ltr">        printf("%s\n", block.hashMerkleRoot.ToString().c_str());</p>
<p style="Normal" xid="2049" props="text-align:left; dom-dir:ltr">        assert(block.hashMerkleRoot == uint256("0x5a2e19825b4162f68602039040f1e05d9f924ff00a3aff7327ca6abd6f3279bc"));</p>
<p style="Normal" xid="2050"><c></c></p>
<p style="Normal" xid="2051" props="text-align:left; dom-dir:ltr">        // If genesis block hash does not match, then generate new genesis hash.</p>
<p style="Normal" xid="2052" props="text-align:left; dom-dir:ltr">        if (false &amp;&amp; block.GetHash() != hashGenesisBlock)</p>
<p style="Normal" xid="2053">        {</p>
<p style="Normal" xid="2054" props="text-align:left; dom-dir:ltr">            printf("Searching for genesis block...\n");</p>
<p style="Normal" xid="2055" props="text-align:left; dom-dir:ltr">            // This will figure out a valid hash and Nonce if you're</p>
<p style="Normal" xid="2056" props="text-align:left; dom-dir:ltr">            // creating a different genesis block:</p>
<p style="Normal" xid="2057" props="text-align:left; dom-dir:ltr">            uint256 hashTarget = CBigNum().SetCompact(block.nBits).getuint256();</p>
<p style="Normal" xid="2058" props="text-align:left; dom-dir:ltr">            uint256 thash;</p>
<p style="Normal" xid="2059" props="text-align:left; dom-dir:ltr">            char scratchpad[SCRYPT_SCRATCHPAD_SIZE];</p>
<p style="Normal" xid="2060"><c></c></p>
<p style="Normal" xid="2061" props="text-align:left; dom-dir:ltr">            loop</p>
<p style="Normal" xid="2062">            {</p>
<p style="Normal" xid="2063" props="text-align:left; dom-dir:ltr">                scrypt_1024_1_1_256_sp(BEGIN(block.nVersion), BEGIN(thash), scratchpad);</p>
<p style="Normal" xid="2064" props="text-align:left; dom-dir:ltr">                if (thash &lt;= hashTarget)</p>
<p style="Normal" xid="2065" props="text-align:left; dom-dir:ltr">                    break;</p>
<p style="Normal" xid="2066" props="text-align:left; dom-dir:ltr">                if ((block.nNonce &amp; 0xFFF) == 0)</p>
<p style="Normal" xid="2067">                {</p>
<p style="Normal" xid="2068" props="text-align:left; dom-dir:ltr">                    printf("nonce %08X: hash = %s (target = %s)\n", block.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());</p>
<p style="Normal" xid="2069">                }</p>
<p style="Normal" xid="2070" props="text-align:left; dom-dir:ltr">                ++block.nNonce;</p>
<p style="Normal" xid="2071" props="text-align:left; dom-dir:ltr">                if (block.nNonce == 0)</p>
<p style="Normal" xid="2072">                {</p>
<p style="Normal" xid="2073" props="text-align:left; dom-dir:ltr">                    printf("NONCE WRAPPED, incrementing time\n");</p>
<p style="Normal" xid="2074" props="text-align:left; dom-dir:ltr">                    ++block.nTime;</p>
<p style="Normal" xid="2075">                }</p>
<p style="Normal" xid="2076">            }</p>
<p style="Normal" xid="2077" props="text-align:left; dom-dir:ltr">            printf("block.nTime = %u \n", block.nTime);</p>
<p style="Normal" xid="2078" props="text-align:left; dom-dir:ltr">            printf("block.nNonce = %u \n", block.nNonce);</p>
<p style="Normal" xid="2079" props="text-align:left; dom-dir:ltr">            printf("block.GetHash = %s\n", block.GetHash().ToString().c_str());</p>
<p style="Normal" xid="2080">        }</p>
<p style="Normal" xid="2081"><c></c></p>
<p style="Normal" xid="2082" props="text-align:left; dom-dir:ltr">        block.print();</p>
<p style="Normal" xid="2083" props="text-align:left; dom-dir:ltr">        assert(block.GetHash() == hashGenesisBlock);</p>
<p style="Normal" xid="2084"><c></c></p>
<p style="Normal" xid="2085" props="text-align:left; dom-dir:ltr">        // Start new block file</p>
<p style="Normal" xid="2086" props="text-align:left; dom-dir:ltr">        unsigned int nFile;</p>
<p style="Normal" xid="2087" props="text-align:left; dom-dir:ltr">        unsigned int nBlockPos;</p>
<p style="Normal" xid="2088" props="text-align:left; dom-dir:ltr">        if (!block.WriteToDisk(nFile, nBlockPos))</p>
<p style="Normal" xid="2089" props="text-align:left; dom-dir:ltr">            return error("LoadBlockIndex() : writing genesis block to disk failed");</p>
<p style="Normal" xid="2090" props="text-align:left; dom-dir:ltr">        if (!block.AddToBlockIndex(nFile, nBlockPos))</p>
<p style="Normal" xid="2091" props="text-align:left; dom-dir:ltr">            return error("LoadBlockIndex() : genesis block not accepted");</p>
<p style="Normal" xid="2092">    }</p>
<p style="Normal" xid="2093"><c></c></p>
<p style="Normal" xid="2094" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="2095">}</p>
<p style="Normal" xid="2096"><c></c></p>
<p style="Normal" xid="2097"><c></c></p>
<p style="Normal" xid="2098"><c></c></p>
<p style="Normal" xid="2099" props="text-align:left; dom-dir:ltr">void PrintBlockTree()</p>
<p style="Normal" xid="2100">{</p>
<p style="Normal" xid="2101" props="text-align:left; dom-dir:ltr">    // precompute tree structure</p>
<p style="Normal" xid="2102" props="text-align:left; dom-dir:ltr">    map&lt;CBlockIndex*, vector&lt;CBlockIndex*&gt; &gt; mapNext;</p>
<p style="Normal" xid="2103" props="text-align:left; dom-dir:ltr">    for (map&lt;uint256, CBlockIndex*&gt;::iterator mi = mapBlockIndex.begin(); mi != mapBlockIndex.end(); ++mi)</p>
<p style="Normal" xid="2104">    {</p>
<p style="Normal" xid="2105" props="text-align:left; dom-dir:ltr">        CBlockIndex* pindex = (*mi).second;</p>
<p style="Normal" xid="2106" props="text-align:left; dom-dir:ltr">        mapNext[pindex-&gt;pprev].push_back(pindex);</p>
<p style="Normal" xid="2107" props="text-align:left; dom-dir:ltr">        // test</p>
<p style="Normal" xid="2108" props="text-align:left; dom-dir:ltr">        //while (rand() % 3 == 0)</p>
<p style="Normal" xid="2109" props="text-align:left; dom-dir:ltr">        //    mapNext[pindex-&gt;pprev].push_back(pindex);</p>
<p style="Normal" xid="2110">    }</p>
<p style="Normal" xid="2111"><c></c></p>
<p style="Normal" xid="2112" props="text-align:left; dom-dir:ltr">    vector&lt;pair&lt;int, CBlockIndex*&gt; &gt; vStack;</p>
<p style="Normal" xid="2113" props="text-align:left; dom-dir:ltr">    vStack.push_back(make_pair(0, pindexGenesisBlock));</p>
<p style="Normal" xid="2114"><c></c></p>
<p style="Normal" xid="2115" props="text-align:left; dom-dir:ltr">    int nPrevCol = 0;</p>
<p style="Normal" xid="2116" props="text-align:left; dom-dir:ltr">    while (!vStack.empty())</p>
<p style="Normal" xid="2117">    {</p>
<p style="Normal" xid="2118" props="text-align:left; dom-dir:ltr">        int nCol = vStack.back().first;</p>
<p style="Normal" xid="2119" props="text-align:left; dom-dir:ltr">        CBlockIndex* pindex = vStack.back().second;</p>
<p style="Normal" xid="2120" props="text-align:left; dom-dir:ltr">        vStack.pop_back();</p>
<p style="Normal" xid="2121"><c></c></p>
<p style="Normal" xid="2122" props="text-align:left; dom-dir:ltr">        // print split or gap</p>
<p style="Normal" xid="2123" props="text-align:left; dom-dir:ltr">        if (nCol &gt; nPrevCol)</p>
<p style="Normal" xid="2124">        {</p>
<p style="Normal" xid="2125" props="text-align:left; dom-dir:ltr">            for (int i = 0; i &lt; nCol-1; i++)</p>
<p style="Normal" xid="2126" props="text-align:left; dom-dir:ltr">                printf("| ");</p>
<p style="Normal" xid="2127" props="text-align:left; dom-dir:ltr">            printf("|\\\n");</p>
<p style="Normal" xid="2128">        }</p>
<p style="Normal" xid="2129" props="text-align:left; dom-dir:ltr">        else if (nCol &lt; nPrevCol)</p>
<p style="Normal" xid="2130">        {</p>
<p style="Normal" xid="2131" props="text-align:left; dom-dir:ltr">            for (int i = 0; i &lt; nCol; i++)</p>
<p style="Normal" xid="2132" props="text-align:left; dom-dir:ltr">                printf("| ");</p>
<p style="Normal" xid="2133" props="text-align:left; dom-dir:ltr">            printf("|\n");</p>
<p style="Normal" xid="2134">       }</p>
<p style="Normal" xid="2135" props="text-align:left; dom-dir:ltr">        nPrevCol = nCol;</p>
<p style="Normal" xid="2136"><c></c></p>
<p style="Normal" xid="2137" props="text-align:left; dom-dir:ltr">        // print columns</p>
<p style="Normal" xid="2138" props="text-align:left; dom-dir:ltr">        for (int i = 0; i &lt; nCol; i++)</p>
<p style="Normal" xid="2139" props="text-align:left; dom-dir:ltr">            printf("| ");</p>
<p style="Normal" xid="2140"><c></c></p>
<p style="Normal" xid="2141" props="text-align:left; dom-dir:ltr">        // print item</p>
<p style="Normal" xid="2142" props="text-align:left; dom-dir:ltr">        CBlock block;</p>
<p style="Normal" xid="2143" props="text-align:left; dom-dir:ltr">        block.ReadFromDisk(pindex);</p>
<p style="Normal" xid="2144" props="text-align:left; dom-dir:ltr">        printf("%d (%u,%u) %s  %s  tx %d",</p>
<p style="Normal" xid="2145" props="text-align:left; dom-dir:ltr">            pindex-&gt;nHeight,</p>
<p style="Normal" xid="2146" props="text-align:left; dom-dir:ltr">            pindex-&gt;nFile,</p>
<p style="Normal" xid="2147" props="text-align:left; dom-dir:ltr">            pindex-&gt;nBlockPos,</p>
<p style="Normal" xid="2148" props="text-align:left; dom-dir:ltr">            block.GetHash().ToString().substr(0,20).c_str(),</p>
<p style="Normal" xid="2149" props="text-align:left; dom-dir:ltr">            DateTimeStrFormat("%x %H:%M:%S", block.GetBlockTime()).c_str(),</p>
<p style="Normal" xid="2150" props="text-align:left; dom-dir:ltr">            block.vtx.size());</p>
<p style="Normal" xid="2151"><c></c></p>
<p style="Normal" xid="2152" props="text-align:left; dom-dir:ltr">        PrintWallets(block);</p>
<p style="Normal" xid="2153"><c></c></p>
<p style="Normal" xid="2154" props="text-align:left; dom-dir:ltr">        // put the main timechain first</p>
<p style="Normal" xid="2155" props="text-align:left; dom-dir:ltr">        vector&lt;CBlockIndex*&gt;&amp; vNext = mapNext[pindex];</p>
<p style="Normal" xid="2156" props="text-align:left; dom-dir:ltr">        for (unsigned int i = 0; i &lt; vNext.size(); i++)</p>
<p style="Normal" xid="2157">        {</p>
<p style="Normal" xid="2158" props="text-align:left; dom-dir:ltr">            if (vNext[i]-&gt;pnext)</p>
<p style="Normal" xid="2159">            {</p>
<p style="Normal" xid="2160" props="text-align:left; dom-dir:ltr">                swap(vNext[0], vNext[i]);</p>
<p style="Normal" xid="2161" props="text-align:left; dom-dir:ltr">                break;</p>
<p style="Normal" xid="2162">            }</p>
<p style="Normal" xid="2163">        }</p>
<p style="Normal" xid="2164"><c></c></p>
<p style="Normal" xid="2165" props="text-align:left; dom-dir:ltr">        // iterate children</p>
<p style="Normal" xid="2166" props="text-align:left; dom-dir:ltr">        for (unsigned int i = 0; i &lt; vNext.size(); i++)</p>
<p style="Normal" xid="2167" props="text-align:left; dom-dir:ltr">            vStack.push_back(make_pair(nCol+i, vNext[i]));</p>
<p style="Normal" xid="2168">    }</p>
<p style="Normal" xid="2169">}</p>
<p style="Normal" xid="2170"><c></c></p>
<p style="Normal" xid="2171" props="text-align:left; dom-dir:ltr">bool LoadExternalBlockFile(FILE* fileIn)</p>
<p style="Normal" xid="2172">{</p>
<p style="Normal" xid="2173" props="text-align:left; dom-dir:ltr">    int nLoaded = 0;</p>
<p style="Normal" xid="2174">    {</p>
<p style="Normal" xid="2175" props="text-align:left; dom-dir:ltr">        LOCK(cs_main);</p>
<p style="Normal" xid="2176" props="text-align:left; dom-dir:ltr">        try {</p>
<p style="Normal" xid="2177" props="text-align:left; dom-dir:ltr">            CAutoFile blkdat(fileIn, SER_DISK, CLIENT_VERSION);</p>
<p style="Normal" xid="2178" props="text-align:left; dom-dir:ltr">            unsigned int nPos = 0;</p>
<p style="Normal" xid="2179" props="text-align:left; dom-dir:ltr">            while (nPos != (unsigned int)-1 &amp;&amp; blkdat.good() &amp;&amp; !fRequestShutdown)</p>
<p style="Normal" xid="2180">            {</p>
<p style="Normal" xid="2181" props="text-align:left; dom-dir:ltr">                unsigned char pchData[65536];</p>
<p style="Normal" xid="2182" props="text-align:left; dom-dir:ltr">                do {</p>
<p style="Normal" xid="2183" props="text-align:left; dom-dir:ltr">                    fseek(blkdat, nPos, SEEK_SET);</p>
<p style="Normal" xid="2184" props="text-align:left; dom-dir:ltr">                    int nRead = fread(pchData, 1, sizeof(pchData), blkdat);</p>
<p style="Normal" xid="2185" props="text-align:left; dom-dir:ltr">                    if (nRead &lt;= 8)</p>
<p style="Normal" xid="2186">                    {</p>
<p style="Normal" xid="2187" props="text-align:left; dom-dir:ltr">                        nPos = (unsigned int)-1;</p>
<p style="Normal" xid="2188" props="text-align:left; dom-dir:ltr">                        break;</p>
<p style="Normal" xid="2189">                    }</p>
<p style="Normal" xid="2190" props="text-align:left; dom-dir:ltr">                    void* nFind = memchr(pchData, pchMessageStart[0], nRead+1-sizeof(pchMessageStart));</p>
<p style="Normal" xid="2191" props="text-align:left; dom-dir:ltr">                    if (nFind)</p>
<p style="Normal" xid="2192">                    {</p>
<p style="Normal" xid="2193" props="text-align:left; dom-dir:ltr">                        if (memcmp(nFind, pchMessageStart, sizeof(pchMessageStart))==0)</p>
<p style="Normal" xid="2194">                        {</p>
<p style="Normal" xid="2195" props="text-align:left; dom-dir:ltr">                            nPos += ((unsigned char*)nFind - pchData) + sizeof(pchMessageStart);</p>
<p style="Normal" xid="2196" props="text-align:left; dom-dir:ltr">                            break;</p>
<p style="Normal" xid="2197">                        }</p>
<p style="Normal" xid="2198" props="text-align:left; dom-dir:ltr">                        nPos += ((unsigned char*)nFind - pchData) + 1;</p>
<p style="Normal" xid="2199">                    }</p>
<p style="Normal" xid="2200" props="text-align:left; dom-dir:ltr">                    else</p>
<p style="Normal" xid="2201" props="text-align:left; dom-dir:ltr">                        nPos += sizeof(pchData) - sizeof(pchMessageStart) + 1;</p>
<p style="Normal" xid="2202" props="text-align:left; dom-dir:ltr">                } while(!fRequestShutdown);</p>
<p style="Normal" xid="2203" props="text-align:left; dom-dir:ltr">                if (nPos == (unsigned int)-1)</p>
<p style="Normal" xid="2204" props="text-align:left; dom-dir:ltr">                    break;</p>
<p style="Normal" xid="2205" props="text-align:left; dom-dir:ltr">                fseek(blkdat, nPos, SEEK_SET);</p>
<p style="Normal" xid="2206" props="text-align:left; dom-dir:ltr">                unsigned int nSize;</p>
<p style="Normal" xid="2207" props="text-align:left; dom-dir:ltr">                blkdat &gt;&gt; nSize;</p>
<p style="Normal" xid="2208" props="text-align:left; dom-dir:ltr">                if (nSize &gt; 0 &amp;&amp; nSize &lt;= MAX_BLOCK_SIZE)</p>
<p style="Normal" xid="2209">                {</p>
<p style="Normal" xid="2210" props="text-align:left; dom-dir:ltr">                    CBlock block;</p>
<p style="Normal" xid="2211" props="text-align:left; dom-dir:ltr">                    blkdat &gt;&gt; block;</p>
<p style="Normal" xid="2212" props="text-align:left; dom-dir:ltr">                    if (ProcessBlock(NULL,&amp;block))</p>
<p style="Normal" xid="2213">                    {</p>
<p style="Normal" xid="2214" props="text-align:left; dom-dir:ltr">                        nLoaded++;</p>
<p style="Normal" xid="2215" props="text-align:left; dom-dir:ltr">                        nPos += 4 + nSize;</p>
<p style="Normal" xid="2216">                    }</p>
<p style="Normal" xid="2217">                }</p>
<p style="Normal" xid="2218">            }</p>
<p style="Normal" xid="2219">        }</p>
<p style="Normal" xid="2220" props="text-align:left; dom-dir:ltr">        catch (std::exception &amp;e) {</p>
<p style="Normal" xid="2221" props="text-align:left; dom-dir:ltr">            printf("%s() : Deserialize or I/O error caught during load\n",</p>
<p style="Normal" xid="2222" props="text-align:left; dom-dir:ltr">                   __PRETTY_FUNCTION__);</p>
<p style="Normal" xid="2223">        }</p>
<p style="Normal" xid="2224">    }</p>
<p style="Normal" xid="2225" props="text-align:left; dom-dir:ltr">    printf("Loaded %i blocks from external file\n", nLoaded);</p>
<p style="Normal" xid="2226" props="text-align:left; dom-dir:ltr">    return nLoaded &gt; 0;</p>
<p style="Normal" xid="2227">}</p>
<p style="Normal" xid="2228"><c></c></p>
<p style="Normal" xid="2229"><c></c></p>
<p style="Normal" xid="2230"><c></c></p>
<p style="Normal" xid="2231"><c></c></p>
<p style="Normal" xid="2232"><c></c></p>
<p style="Normal" xid="2233"><c></c></p>
<p style="Normal" xid="2234"><c></c></p>
<p style="Normal" xid="2235"><c></c></p>
<p style="Normal" xid="2236"><c></c></p>
<p style="Normal" xid="2237">//////////////////////////////////////////////////////////////////////////////</p>
<p style="Normal" xid="2238">//</p>
<p style="Normal" xid="2239" props="text-align:left; dom-dir:ltr">// CAlert</p>
<p style="Normal" xid="2240">//</p>
<p style="Normal" xid="2241"><c></c></p>
<p style="Normal" xid="2242" props="text-align:left; dom-dir:ltr">map&lt;uint256, CAlert&gt; mapAlerts;</p>
<p style="Normal" xid="2243" props="text-align:left; dom-dir:ltr">CCriticalSection cs_mapAlerts;</p>
<p style="Normal" xid="2244"><c></c></p>
<p style="Normal" xid="2245" props="text-align:left; dom-dir:ltr">string GetWarnings(string strFor)</p>
<p style="Normal" xid="2246">{</p>
<p style="Normal" xid="2247" props="text-align:left; dom-dir:ltr">    int nPriority = 0;</p>
<p style="Normal" xid="2248" props="text-align:left; dom-dir:ltr">    string strStatusBar;</p>
<p style="Normal" xid="2249" props="text-align:left; dom-dir:ltr">    string strRPC;</p>
<p style="Normal" xid="2250" props="text-align:left; dom-dir:ltr">    if (GetBoolArg("-testsafemode"))</p>
<p style="Normal" xid="2251" props="text-align:left; dom-dir:ltr">        strRPC = "test";</p>
<p style="Normal" xid="2252"><c></c></p>
<p style="Normal" xid="2253" props="text-align:left; dom-dir:ltr">    // Misc warnings like out of disk space and clock is wrong</p>
<p style="Normal" xid="2254" props="text-align:left; dom-dir:ltr">    if (strMiscWarning != "")</p>
<p style="Normal" xid="2255">    {</p>
<p style="Normal" xid="2256" props="text-align:left; dom-dir:ltr">        nPriority = 1000;</p>
<p style="Normal" xid="2257" props="text-align:left; dom-dir:ltr">        strStatusBar = strMiscWarning;</p>
<p style="Normal" xid="2258">    }</p>
<p style="Normal" xid="2259"><c></c></p>
<p style="Normal" xid="2260" props="text-align:left; dom-dir:ltr">    // Longer invalid proof-of-work chain</p>
<p style="Normal" xid="2261" props="text-align:left; dom-dir:ltr">    if (pindexBest &amp;&amp; bnBestInvalidWork &gt; bnBestChainWork + pindexBest-&gt;GetBlockWork() * 6)</p>
<p style="Normal" xid="2262">    {</p>
<p style="Normal" xid="2263" props="text-align:left; dom-dir:ltr">        nPriority = 2000;</p>
<p style="Normal" xid="2264" props="text-align:left; dom-dir:ltr">        strStatusBar = strRPC = "WARNING: Displayed transactions may not be correct!  You may need to upgrade, or other nodes may need to upgrade.";</p>
<p style="Normal" xid="2265">    }</p>
<p style="Normal" xid="2266"><c></c></p>
<p style="Normal" xid="2267" props="text-align:left; dom-dir:ltr">    // Alerts</p>
<p style="Normal" xid="2268">    {</p>
<p style="Normal" xid="2269" props="text-align:left; dom-dir:ltr">        LOCK(cs_mapAlerts);</p>
<p style="Normal" xid="2270" props="text-align:left; dom-dir:ltr">        BOOST_FOREACH(PAIRTYPE(const uint256, CAlert)&amp; item, mapAlerts)</p>
<p style="Normal" xid="2271">        {</p>
<p style="Normal" xid="2272" props="text-align:left; dom-dir:ltr">            const CAlert&amp; alert = item.second;</p>
<p style="Normal" xid="2273" props="text-align:left; dom-dir:ltr">            if (alert.AppliesToMe() &amp;&amp; alert.nPriority &gt; nPriority)</p>
<p style="Normal" xid="2274">            {</p>
<p style="Normal" xid="2275" props="text-align:left; dom-dir:ltr">                nPriority = alert.nPriority;</p>
<p style="Normal" xid="2276" props="text-align:left; dom-dir:ltr">                strStatusBar = alert.strStatusBar;</p>
<p style="Normal" xid="2277">            }</p>
<p style="Normal" xid="2278">        }</p>
<p style="Normal" xid="2279">    }</p>
<p style="Normal" xid="2280"><c></c></p>
<p style="Normal" xid="2281" props="text-align:left; dom-dir:ltr">    if (strFor == "statusbar")</p>
<p style="Normal" xid="2282" props="text-align:left; dom-dir:ltr">        return strStatusBar;</p>
<p style="Normal" xid="2283" props="text-align:left; dom-dir:ltr">    else if (strFor == "rpc")</p>
<p style="Normal" xid="2284" props="text-align:left; dom-dir:ltr">        return strRPC;</p>
<p style="Normal" xid="2285" props="text-align:left; dom-dir:ltr">    assert(!"GetWarnings() : invalid parameter");</p>
<p style="Normal" xid="2286" props="text-align:left; dom-dir:ltr">    return "error";</p>
<p style="Normal" xid="2287">}</p>
<p style="Normal" xid="2288"><c></c></p>
<p style="Normal" xid="2289" props="text-align:left; dom-dir:ltr">CAlert CAlert::getAlertByHash(const uint256 &amp;hash)</p>
<p style="Normal" xid="2290">{</p>
<p style="Normal" xid="2291" props="text-align:left; dom-dir:ltr">    CAlert retval;</p>
<p style="Normal" xid="2292">    {</p>
<p style="Normal" xid="2293" props="text-align:left; dom-dir:ltr">        LOCK(cs_mapAlerts);</p>
<p style="Normal" xid="2294" props="text-align:left; dom-dir:ltr">        map&lt;uint256, CAlert&gt;::iterator mi = mapAlerts.find(hash);</p>
<p style="Normal" xid="2295" props="text-align:left; dom-dir:ltr">        if(mi != mapAlerts.end())</p>
<p style="Normal" xid="2296" props="text-align:left; dom-dir:ltr">            retval = mi-&gt;second;</p>
<p style="Normal" xid="2297">    }</p>
<p style="Normal" xid="2298" props="text-align:left; dom-dir:ltr">    return retval;</p>
<p style="Normal" xid="2299">}</p>
<p style="Normal" xid="2300"><c></c></p>
<p style="Normal" xid="2301" props="text-align:left; dom-dir:ltr">bool CAlert::ProcessAlert()</p>
<p style="Normal" xid="2302">{</p>
<p style="Normal" xid="2303" props="text-align:left; dom-dir:ltr">    if (!CheckSignature())</p>
<p style="Normal" xid="2304" props="text-align:left; dom-dir:ltr">        return false;</p>
<p style="Normal" xid="2305" props="text-align:left; dom-dir:ltr">    if (!IsInEffect())</p>
<p style="Normal" xid="2306" props="text-align:left; dom-dir:ltr">        return false;</p>
<p style="Normal" xid="2307"><c></c></p>
<p style="Normal" xid="2308">    {</p>
<p style="Normal" xid="2309" props="text-align:left; dom-dir:ltr">        LOCK(cs_mapAlerts);</p>
<p style="Normal" xid="2310" props="text-align:left; dom-dir:ltr">        // Cancel previous alerts</p>
<p style="Normal" xid="2311" props="text-align:left; dom-dir:ltr">        for (map&lt;uint256, CAlert&gt;::iterator mi = mapAlerts.begin(); mi != mapAlerts.end();)</p>
<p style="Normal" xid="2312">        {</p>
<p style="Normal" xid="2313" props="text-align:left; dom-dir:ltr">            const CAlert&amp; alert = (*mi).second;</p>
<p style="Normal" xid="2314" props="text-align:left; dom-dir:ltr">            if (Cancels(alert))</p>
<p style="Normal" xid="2315">            {</p>
<p style="Normal" xid="2316" props="text-align:left; dom-dir:ltr">                printf("cancelling alert %d\n", alert.nID);</p>
<p style="Normal" xid="2317" props="text-align:left; dom-dir:ltr">                uiInterface.NotifyAlertChanged((*mi).first, CT_DELETED);</p>
<p style="Normal" xid="2318" props="text-align:left; dom-dir:ltr">                mapAlerts.erase(mi++);</p>
<p style="Normal" xid="2319">            }</p>
<p style="Normal" xid="2320" props="text-align:left; dom-dir:ltr">            else if (!alert.IsInEffect())</p>
<p style="Normal" xid="2321">            {</p>
<p style="Normal" xid="2322" props="text-align:left; dom-dir:ltr">                printf("expiring alert %d\n", alert.nID);</p>
<p style="Normal" xid="2323" props="text-align:left; dom-dir:ltr">                uiInterface.NotifyAlertChanged((*mi).first, CT_DELETED);</p>
<p style="Normal" xid="2324" props="text-align:left; dom-dir:ltr">                mapAlerts.erase(mi++);</p>
<p style="Normal" xid="2325">            }</p>
<p style="Normal" xid="2326" props="text-align:left; dom-dir:ltr">            else</p>
<p style="Normal" xid="2327" props="text-align:left; dom-dir:ltr">                mi++;</p>
<p style="Normal" xid="2328">        }</p>
<p style="Normal" xid="2329"><c></c></p>
<p style="Normal" xid="2330" props="text-align:left; dom-dir:ltr">        // Check if this alert has been cancelled</p>
<p style="Normal" xid="2331" props="text-align:left; dom-dir:ltr">        BOOST_FOREACH(PAIRTYPE(const uint256, CAlert)&amp; item, mapAlerts)</p>
<p style="Normal" xid="2332">        {</p>
<p style="Normal" xid="2333" props="text-align:left; dom-dir:ltr">            const CAlert&amp; alert = item.second;</p>
<p style="Normal" xid="2334" props="text-align:left; dom-dir:ltr">            if (alert.Cancels(*this))</p>
<p style="Normal" xid="2335">            {</p>
<p style="Normal" xid="2336" props="text-align:left; dom-dir:ltr">                printf("alert already cancelled by %d\n", alert.nID);</p>
<p style="Normal" xid="2337" props="text-align:left; dom-dir:ltr">                return false;</p>
<p style="Normal" xid="2338">            }</p>
<p style="Normal" xid="2339">        }</p>
<p style="Normal" xid="2340"><c></c></p>
<p style="Normal" xid="2341" props="text-align:left; dom-dir:ltr">        // Add to mapAlerts</p>
<p style="Normal" xid="2342" props="text-align:left; dom-dir:ltr">        mapAlerts.insert(make_pair(GetHash(), *this));</p>
<p style="Normal" xid="2343" props="text-align:left; dom-dir:ltr">        // Notify UI if it applies to me</p>
<p style="Normal" xid="2344" props="text-align:left; dom-dir:ltr">        if(AppliesToMe())</p>
<p style="Normal" xid="2345" props="text-align:left; dom-dir:ltr">            uiInterface.NotifyAlertChanged(GetHash(), CT_NEW);</p>
<p style="Normal" xid="2346">    }</p>
<p style="Normal" xid="2347"><c></c></p>
<p style="Normal" xid="2348" props="text-align:left; dom-dir:ltr">    printf("accepted alert %d, AppliesToMe()=%d\n", nID, AppliesToMe());</p>
<p style="Normal" xid="2349" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="2350">}</p>
<p style="Normal" xid="2351"><c></c></p>
<p style="Normal" xid="2352"><c></c></p>
<p style="Normal" xid="2353"><c></c></p>
<p style="Normal" xid="2354"><c></c></p>
<p style="Normal" xid="2355"><c></c></p>
<p style="Normal" xid="2356"><c></c></p>
<p style="Normal" xid="2357"><c></c></p>
<p style="Normal" xid="2358"><c></c></p>
<p style="Normal" xid="2359">//////////////////////////////////////////////////////////////////////////////</p>
<p style="Normal" xid="2360">//</p>
<p style="Normal" xid="2361" props="text-align:left; dom-dir:ltr">// Messages</p>
<p style="Normal" xid="2362">//</p>
<p style="Normal" xid="2363"><c></c></p>
<p style="Normal" xid="2364"><c></c></p>
<p style="Normal" xid="2365" props="text-align:left; dom-dir:ltr">bool static AlreadyHave(CTxDB&amp; txdb, const CInv&amp; inv)</p>
<p style="Normal" xid="2366">{</p>
<p style="Normal" xid="2367" props="text-align:left; dom-dir:ltr">    switch (inv.type)</p>
<p style="Normal" xid="2368">    {</p>
<p style="Normal" xid="2369" props="text-align:left; dom-dir:ltr">    case MSG_TX:</p>
<p style="Normal" xid="2370">        {</p>
<p style="Normal" xid="2371" props="text-align:left; dom-dir:ltr">        bool txInMap = false;</p>
<p style="Normal" xid="2372">            {</p>
<p style="Normal" xid="2373" props="text-align:left; dom-dir:ltr">            LOCK(mempool.cs);</p>
<p style="Normal" xid="2374" props="text-align:left; dom-dir:ltr">            txInMap = (mempool.exists(inv.hash));</p>
<p style="Normal" xid="2375">            }</p>
<p style="Normal" xid="2376" props="text-align:left; dom-dir:ltr">        return txInMap ||</p>
<p style="Normal" xid="2377" props="text-align:left; dom-dir:ltr">               mapOrphanTransactions.count(inv.hash) ||</p>
<p style="Normal" xid="2378" props="text-align:left; dom-dir:ltr">               txdb.ContainsTx(inv.hash);</p>
<p style="Normal" xid="2379">        }</p>
<p style="Normal" xid="2380"><c></c></p>
<p style="Normal" xid="2381" props="text-align:left; dom-dir:ltr">    case MSG_BLOCK:</p>
<p style="Normal" xid="2382" props="text-align:left; dom-dir:ltr">        return mapBlockIndex.count(inv.hash) ||</p>
<p style="Normal" xid="2383" props="text-align:left; dom-dir:ltr">               mapOrphanBlocks.count(inv.hash);</p>
<p style="Normal" xid="2384">    }</p>
<p style="Normal" xid="2385" props="text-align:left; dom-dir:ltr">    // Don't know what it is, just say we already got one</p>
<p style="Normal" xid="2386" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="2387">}</p>
<p style="Normal" xid="2388"><c></c></p>
<p style="Normal" xid="2389"><c></c></p>
<p style="Normal" xid="2390"><c></c></p>
<p style="Normal" xid="2391"><c></c></p>
<p style="Normal" xid="2392" props="text-align:left; dom-dir:ltr">// The message start string is designed to be unlikely to occur in normal data.</p>
<p style="Normal" xid="2393" props="text-align:left; dom-dir:ltr">// The characters are rarely used upper ascii, not valid as UTF-8, and produce</p>
<p style="Normal" xid="2394" props="text-align:left; dom-dir:ltr">// a large 4-byte int at any alignment.</p>
<p style="Normal" xid="2395" props="text-align:left; dom-dir:ltr">unsigned char pchMessageStart[4] = { 0xfc, 0xd9, 0xb7, 0xdd };</p>
<p style="Normal" xid="2396"><c></c></p>
<p style="Normal" xid="2397"><c></c></p>
<p style="Normal" xid="2398" props="text-align:left; dom-dir:ltr">bool static ProcessMessage(CNode* pfrom, string strCommand, CDataStream&amp; vRecv)</p>
<p style="Normal" xid="2399">{</p>
<p style="Normal" xid="2400" props="text-align:left; dom-dir:ltr">    static map&lt;CService, CPubKey&gt; mapReuseKey;</p>
<p style="Normal" xid="2401" props="text-align:left; dom-dir:ltr">    RandAddSeedPerfmon();</p>
<p style="Normal" xid="2402" props="text-align:left; dom-dir:ltr">    if (fDebug)</p>
<p style="Normal" xid="2403" props="text-align:left; dom-dir:ltr">        printf("received: %s (%d bytes)\n", strCommand.c_str(), vRecv.size());</p>
<p style="Normal" xid="2404" props="text-align:left; dom-dir:ltr">    if (mapArgs.count("-dropmessagestest") &amp;&amp; GetRand(atoi(mapArgs["-dropmessagestest"])) == 0)</p>
<p style="Normal" xid="2405">    {</p>
<p style="Normal" xid="2406" props="text-align:left; dom-dir:ltr">        printf("dropmessagestest DROPPING RECV MESSAGE\n");</p>
<p style="Normal" xid="2407" props="text-align:left; dom-dir:ltr">        return true;</p>
<p style="Normal" xid="2408">    }</p>
<p style="Normal" xid="2409"><c></c></p>
<p style="Normal" xid="2410"><c></c></p>
<p style="Normal" xid="2411"><c></c></p>
<p style="Normal" xid="2412"><c></c></p>
<p style="Normal" xid="2413"><c></c></p>
<p style="Normal" xid="2414" props="text-align:left; dom-dir:ltr">    if (strCommand == "version")</p>
<p style="Normal" xid="2415">    {</p>
<p style="Normal" xid="2416" props="text-align:left; dom-dir:ltr">        // Each connection can only send one version message</p>
<p style="Normal" xid="2417" props="text-align:left; dom-dir:ltr">        if (pfrom-&gt;nVersion != 0)</p>
<p style="Normal" xid="2418">        {</p>
<p style="Normal" xid="2419" props="text-align:left; dom-dir:ltr">            pfrom-&gt;Misbehaving(1);</p>
<p style="Normal" xid="2420" props="text-align:left; dom-dir:ltr">            return false;</p>
<p style="Normal" xid="2421">        }</p>
<p style="Normal" xid="2422"><c></c></p>
<p style="Normal" xid="2423" props="text-align:left; dom-dir:ltr">        int64 nTime;</p>
<p style="Normal" xid="2424" props="text-align:left; dom-dir:ltr">        CAddress addrMe;</p>
<p style="Normal" xid="2425" props="text-align:left; dom-dir:ltr">        CAddress addrFrom;</p>
<p style="Normal" xid="2426" props="text-align:left; dom-dir:ltr">        uint64 nNonce = 1;</p>
<p style="Normal" xid="2427" props="text-align:left; dom-dir:ltr">        vRecv &gt;&gt; pfrom-&gt;nVersion &gt;&gt; pfrom-&gt;nServices &gt;&gt; nTime &gt;&gt; addrMe;</p>
<p style="Normal" xid="2428" props="text-align:left; dom-dir:ltr">        if (pfrom-&gt;nVersion &lt; MIN_PROTO_VERSION)</p>
<p style="Normal" xid="2429">        {</p>
<p style="Normal" xid="2430" props="text-align:left; dom-dir:ltr">            // Since February 20, 2012, the protocol is initiated at version 209,</p>
<p style="Normal" xid="2431" props="text-align:left; dom-dir:ltr">            // and earlier versions are no longer supported</p>
<p style="Normal" xid="2432" props="text-align:left; dom-dir:ltr">            printf("partner %s using obsolete version %i; disconnecting\n", pfrom-&gt;addr.ToString().c_str(), pfrom-&gt;nVersion);</p>
<p style="Normal" xid="2433" props="text-align:left; dom-dir:ltr">            pfrom-&gt;fDisconnect = true;</p>
<p style="Normal" xid="2434" props="text-align:left; dom-dir:ltr">            return false;</p>
<p style="Normal" xid="2435">        }</p>
<p style="Normal" xid="2436"><c></c></p>
<p style="Normal" xid="2437" props="text-align:left; dom-dir:ltr">        if (pfrom-&gt;nVersion == 10300)</p>
<p style="Normal" xid="2438" props="text-align:left; dom-dir:ltr">            pfrom-&gt;nVersion = 300;</p>
<p style="Normal" xid="2439" props="text-align:left; dom-dir:ltr">        if (!vRecv.empty())</p>
<p style="Normal" xid="2440" props="text-align:left; dom-dir:ltr">            vRecv &gt;&gt; addrFrom &gt;&gt; nNonce;</p>
<p style="Normal" xid="2441" props="text-align:left; dom-dir:ltr">        if (!vRecv.empty())</p>
<p style="Normal" xid="2442" props="text-align:left; dom-dir:ltr">            vRecv &gt;&gt; pfrom-&gt;strSubVer;</p>
<p style="Normal" xid="2443" props="text-align:left; dom-dir:ltr">        if (!vRecv.empty())</p>
<p style="Normal" xid="2444" props="text-align:left; dom-dir:ltr">            vRecv &gt;&gt; pfrom-&gt;nStartingHeight;</p>
<p style="Normal" xid="2445"><c></c></p>
<p style="Normal" xid="2446" props="text-align:left; dom-dir:ltr">        if (pfrom-&gt;fInbound &amp;&amp; addrMe.IsRoutable())</p>
<p style="Normal" xid="2447">        {</p>
<p style="Normal" xid="2448" props="text-align:left; dom-dir:ltr">            pfrom-&gt;addrLocal = addrMe;</p>
<p style="Normal" xid="2449" props="text-align:left; dom-dir:ltr">            SeenLocal(addrMe);</p>
<p style="Normal" xid="2450">        }</p>
<p style="Normal" xid="2451"><c></c></p>
<p style="Normal" xid="2452" props="text-align:left; dom-dir:ltr">        // Disconnect if we connected to ourself</p>
<p style="Normal" xid="2453" props="text-align:left; dom-dir:ltr">        if (nNonce == nLocalHostNonce &amp;&amp; nNonce &gt; 1)</p>
<p style="Normal" xid="2454">        {</p>
<p style="Normal" xid="2455" props="text-align:left; dom-dir:ltr">            printf("connected to self at %s, disconnecting\n", pfrom-&gt;addr.ToString().c_str());</p>
<p style="Normal" xid="2456" props="text-align:left; dom-dir:ltr">            pfrom-&gt;fDisconnect = true;</p>
<p style="Normal" xid="2457" props="text-align:left; dom-dir:ltr">            return true;</p>
<p style="Normal" xid="2458">        }</p>
<p style="Normal" xid="2459"><c></c></p>
<p style="Normal" xid="2460" props="text-align:left; dom-dir:ltr">        // Be shy and don't send version until we hear</p>
<p style="Normal" xid="2461" props="text-align:left; dom-dir:ltr">        if (pfrom-&gt;fInbound)</p>
<p style="Normal" xid="2462" props="text-align:left; dom-dir:ltr">            pfrom-&gt;PushVersion();</p>
<p style="Normal" xid="2463"><c></c></p>
<p style="Normal" xid="2464" props="text-align:left; dom-dir:ltr">        pfrom-&gt;fClient = !(pfrom-&gt;nServices &amp; NODE_NETWORK);</p>
<p style="Normal" xid="2465"><c></c></p>
<p style="Normal" xid="2466" props="text-align:left; dom-dir:ltr">        AddTimeData(pfrom-&gt;addr, nTime);</p>
<p style="Normal" xid="2467"><c></c></p>
<p style="Normal" xid="2468" props="text-align:left; dom-dir:ltr">        // Change version</p>
<p style="Normal" xid="2469" props="text-align:left; dom-dir:ltr">        pfrom-&gt;PushMessage("verack");</p>
<p style="Normal" xid="2470" props="text-align:left; dom-dir:ltr">        pfrom-&gt;vSend.SetVersion(min(pfrom-&gt;nVersion, PROTOCOL_VERSION));</p>
<p style="Normal" xid="2471"><c></c></p>
<p style="Normal" xid="2472" props="text-align:left; dom-dir:ltr">        if (!pfrom-&gt;fInbound)</p>
<p style="Normal" xid="2473">        {</p>
<p style="Normal" xid="2474" props="text-align:left; dom-dir:ltr">            // Advertise our address</p>
<p style="Normal" xid="2475" props="text-align:left; dom-dir:ltr">            if (!fNoListen &amp;&amp; !IsInitialBlockDownload())</p>
<p style="Normal" xid="2476">            {</p>
<p style="Normal" xid="2477" props="text-align:left; dom-dir:ltr">                CAddress addr = GetLocalAddress(&amp;pfrom-&gt;addr);</p>
<p style="Normal" xid="2478" props="text-align:left; dom-dir:ltr">                if (addr.IsRoutable())</p>
<p style="Normal" xid="2479" props="text-align:left; dom-dir:ltr">                    pfrom-&gt;PushAddress(addr);</p>
<p style="Normal" xid="2480">            }</p>
<p style="Normal" xid="2481"><c></c></p>
<p style="Normal" xid="2482" props="text-align:left; dom-dir:ltr">            // Get recent addresses</p>
<p style="Normal" xid="2483" props="text-align:left; dom-dir:ltr">            if (pfrom-&gt;fOneShot || pfrom-&gt;nVersion &gt;= CADDR_TIME_VERSION || addrman.size() &lt; 1000)</p>
<p style="Normal" xid="2484">            {</p>
<p style="Normal" xid="2485" props="text-align:left; dom-dir:ltr">                pfrom-&gt;PushMessage("getaddr");</p>
<p style="Normal" xid="2486" props="text-align:left; dom-dir:ltr">                pfrom-&gt;fGetAddr = true;</p>
<p style="Normal" xid="2487">            }</p>
<p style="Normal" xid="2488" props="text-align:left; dom-dir:ltr">            addrman.Good(pfrom-&gt;addr);</p>
<p style="Normal" xid="2489" props="text-align:left; dom-dir:ltr">        } else {</p>
<p style="Normal" xid="2490" props="text-align:left; dom-dir:ltr">            if (((CNetAddr)pfrom-&gt;addr) == (CNetAddr)addrFrom)</p>
<p style="Normal" xid="2491">            {</p>
<p style="Normal" xid="2492" props="text-align:left; dom-dir:ltr">                addrman.Add(addrFrom, addrFrom);</p>
<p style="Normal" xid="2493" props="text-align:left; dom-dir:ltr">                addrman.Good(addrFrom);</p>
<p style="Normal" xid="2494">            }</p>
<p style="Normal" xid="2495">        }</p>
<p style="Normal" xid="2496"><c></c></p>
<p style="Normal" xid="2497" props="text-align:left; dom-dir:ltr">        // Ask the first connected node for block updates</p>
<p style="Normal" xid="2498" props="text-align:left; dom-dir:ltr">        static int nAskedForBlocks = 0;</p>
<p style="Normal" xid="2499" props="text-align:left; dom-dir:ltr">        if (!pfrom-&gt;fClient &amp;&amp; !pfrom-&gt;fOneShot &amp;&amp;</p>
<p style="Normal" xid="2500" props="text-align:left; dom-dir:ltr">            (pfrom-&gt;nVersion &lt; NOBLKS_VERSION_START ||</p>
<p style="Normal" xid="2501" props="text-align:left; dom-dir:ltr">             pfrom-&gt;nVersion &gt;= NOBLKS_VERSION_END) &amp;&amp;</p>
<p style="Normal" xid="2502" props="text-align:left; dom-dir:ltr">             (nAskedForBlocks &lt; 1 || vNodes.size() &lt;= 1))</p>
<p style="Normal" xid="2503">        {</p>
<p style="Normal" xid="2504" props="text-align:left; dom-dir:ltr">            nAskedForBlocks++;</p>
<p style="Normal" xid="2505" props="text-align:left; dom-dir:ltr">            pfrom-&gt;PushGetBlocks(pindexBest, uint256(0));</p>
<p style="Normal" xid="2506">        }</p>
<p style="Normal" xid="2507"><c></c></p>
<p style="Normal" xid="2508" props="text-align:left; dom-dir:ltr">        // Relay alerts</p>
<p style="Normal" xid="2509">        {</p>
<p style="Normal" xid="2510" props="text-align:left; dom-dir:ltr">            LOCK(cs_mapAlerts);</p>
<p style="Normal" xid="2511" props="text-align:left; dom-dir:ltr">            BOOST_FOREACH(PAIRTYPE(const uint256, CAlert)&amp; item, mapAlerts)</p>
<p style="Normal" xid="2512" props="text-align:left; dom-dir:ltr">                item.second.RelayTo(pfrom);</p>
<p style="Normal" xid="2513">        }</p>
<p style="Normal" xid="2514"><c></c></p>
<p style="Normal" xid="2515" props="text-align:left; dom-dir:ltr">        pfrom-&gt;fSuccessfullyConnected = true;</p>
<p style="Normal" xid="2516"><c></c></p>
<p style="Normal" xid="2517" props="text-align:left; dom-dir:ltr">        printf("receive version message: version %d, blocks=%d, us=%s, them=%s, peer=%s\n", pfrom-&gt;nVersion, pfrom-&gt;nStartingHeight, addrMe.ToString().c_str(), addrFrom.ToString().c_str(), pfrom-&gt;addr.ToString().c_str());</p>
<p style="Normal" xid="2518"><c></c></p>
<p style="Normal" xid="2519" props="text-align:left; dom-dir:ltr">        cPeerBlockCounts.input(pfrom-&gt;nStartingHeight);</p>
<p style="Normal" xid="2520">    }</p>
<p style="Normal" xid="2521"><c></c></p>
<p style="Normal" xid="2522"><c></c></p>
<p style="Normal" xid="2523" props="text-align:left; dom-dir:ltr">    else if (pfrom-&gt;nVersion == 0)</p>
<p style="Normal" xid="2524">    {</p>
<p style="Normal" xid="2525" props="text-align:left; dom-dir:ltr">        // Must have a version message before anything else</p>
<p style="Normal" xid="2526" props="text-align:left; dom-dir:ltr">        pfrom-&gt;Misbehaving(1);</p>
<p style="Normal" xid="2527" props="text-align:left; dom-dir:ltr">        return false;</p>
<p style="Normal" xid="2528">    }</p>
<p style="Normal" xid="2529"><c></c></p>
<p style="Normal" xid="2530"><c></c></p>
<p style="Normal" xid="2531" props="text-align:left; dom-dir:ltr">    else if (strCommand == "verack")</p>
<p style="Normal" xid="2532">    {</p>
<p style="Normal" xid="2533" props="text-align:left; dom-dir:ltr">        pfrom-&gt;vRecv.SetVersion(min(pfrom-&gt;nVersion, PROTOCOL_VERSION));</p>
<p style="Normal" xid="2534">    }</p>
<p style="Normal" xid="2535"><c></c></p>
<p style="Normal" xid="2536"><c></c></p>
<p style="Normal" xid="2537" props="text-align:left; dom-dir:ltr">    else if (strCommand == "addr")</p>
<p style="Normal" xid="2538">    {</p>
<p style="Normal" xid="2539" props="text-align:left; dom-dir:ltr">        vector&lt;CAddress&gt; vAddr;</p>
<p style="Normal" xid="2540" props="text-align:left; dom-dir:ltr">        vRecv &gt;&gt; vAddr;</p>
<p style="Normal" xid="2541"><c></c></p>
<p style="Normal" xid="2542" props="text-align:left; dom-dir:ltr">        // Don't want addr from older versions unless seeding</p>
<p style="Normal" xid="2543" props="text-align:left; dom-dir:ltr">        if (pfrom-&gt;nVersion &lt; CADDR_TIME_VERSION &amp;&amp; addrman.size() &gt; 1000)</p>
<p style="Normal" xid="2544" props="text-align:left; dom-dir:ltr">            return true;</p>
<p style="Normal" xid="2545" props="text-align:left; dom-dir:ltr">        if (vAddr.size() &gt; 1000)</p>
<p style="Normal" xid="2546">        {</p>
<p style="Normal" xid="2547" props="text-align:left; dom-dir:ltr">            pfrom-&gt;Misbehaving(20);</p>
<p style="Normal" xid="2548" props="text-align:left; dom-dir:ltr">            return error("message addr size() = %d", vAddr.size());</p>
<p style="Normal" xid="2549">        }</p>
<p style="Normal" xid="2550"><c></c></p>
<p style="Normal" xid="2551" props="text-align:left; dom-dir:ltr">        // Store the new addresses</p>
<p style="Normal" xid="2552" props="text-align:left; dom-dir:ltr">        vector&lt;CAddress&gt; vAddrOk;</p>
<p style="Normal" xid="2553" props="text-align:left; dom-dir:ltr">        int64 nNow = GetAdjustedTime();</p>
<p style="Normal" xid="2554" props="text-align:left; dom-dir:ltr">        int64 nSince = nNow - 10 * 60;</p>
<p style="Normal" xid="2555" props="text-align:left; dom-dir:ltr">        BOOST_FOREACH(CAddress&amp; addr, vAddr)</p>
<p style="Normal" xid="2556">        {</p>
<p style="Normal" xid="2557" props="text-align:left; dom-dir:ltr">            if (fShutdown)</p>
<p style="Normal" xid="2558" props="text-align:left; dom-dir:ltr">                return true;</p>
<p style="Normal" xid="2559" props="text-align:left; dom-dir:ltr">            if (addr.nTime &lt;= 100000000 || addr.nTime &gt; nNow + 10 * 60)</p>
<p style="Normal" xid="2560" props="text-align:left; dom-dir:ltr">                addr.nTime = nNow - 5 * 24 * 60 * 60;</p>
<p style="Normal" xid="2561" props="text-align:left; dom-dir:ltr">            pfrom-&gt;AddAddressKnown(addr);</p>
<p style="Normal" xid="2562" props="text-align:left; dom-dir:ltr">            bool fReachable = IsReachable(addr);</p>
<p style="Normal" xid="2563" props="text-align:left; dom-dir:ltr">            if (addr.nTime &gt; nSince &amp;&amp; !pfrom-&gt;fGetAddr &amp;&amp; vAddr.size() &lt;= 10 &amp;&amp; addr.IsRoutable())</p>
<p style="Normal" xid="2564">            {</p>
<p style="Normal" xid="2565" props="text-align:left; dom-dir:ltr">                // Relay to a limited number of other nodes</p>
<p style="Normal" xid="2566">                {</p>
<p style="Normal" xid="2567" props="text-align:left; dom-dir:ltr">                    LOCK(cs_vNodes);</p>
<p style="Normal" xid="2568" props="text-align:left; dom-dir:ltr">                    // Use deterministic randomness to send to the same nodes for 24 hours</p>
<p style="Normal" xid="2569" props="text-align:left; dom-dir:ltr">                    // at a time so the setAddrKnowns of the chosen nodes prevent repeats</p>
<p style="Normal" xid="2570" props="text-align:left; dom-dir:ltr">                    static uint256 hashSalt;</p>
<p style="Normal" xid="2571" props="text-align:left; dom-dir:ltr">                    if (hashSalt == 0)</p>
<p style="Normal" xid="2572" props="text-align:left; dom-dir:ltr">                        hashSalt = GetRandHash();</p>
<p style="Normal" xid="2573" props="text-align:left; dom-dir:ltr">                    uint64 hashAddr = addr.GetHash();</p>
<p style="Normal" xid="2574" props="text-align:left; dom-dir:ltr">                    uint256 hashRand = hashSalt ^ (hashAddr&lt;&lt;32) ^ ((GetTime()+hashAddr)/(24*60*60));</p>
<p style="Normal" xid="2575" props="text-align:left; dom-dir:ltr">                    hashRand = Hash(BEGIN(hashRand), END(hashRand));</p>
<p style="Normal" xid="2576" props="text-align:left; dom-dir:ltr">                    multimap&lt;uint256, CNode*&gt; mapMix;</p>
<p style="Normal" xid="2577" props="text-align:left; dom-dir:ltr">                    BOOST_FOREACH(CNode* pnode, vNodes)</p>
<p style="Normal" xid="2578">                    {</p>
<p style="Normal" xid="2579" props="text-align:left; dom-dir:ltr">                        if (pnode-&gt;nVersion &lt; CADDR_TIME_VERSION)</p>
<p style="Normal" xid="2580" props="text-align:left; dom-dir:ltr">                            continue;</p>
<p style="Normal" xid="2581" props="text-align:left; dom-dir:ltr">                        unsigned int nPointer;</p>
<p style="Normal" xid="2582" props="text-align:left; dom-dir:ltr">                        memcpy(&amp;nPointer, &amp;pnode, sizeof(nPointer));</p>
<p style="Normal" xid="2583" props="text-align:left; dom-dir:ltr">                        uint256 hashKey = hashRand ^ nPointer;</p>
<p style="Normal" xid="2584" props="text-align:left; dom-dir:ltr">                        hashKey = Hash(BEGIN(hashKey), END(hashKey));</p>
<p style="Normal" xid="2585" props="text-align:left; dom-dir:ltr">                        mapMix.insert(make_pair(hashKey, pnode));</p>
<p style="Normal" xid="2586">                    }</p>
<p style="Normal" xid="2587" props="text-align:left; dom-dir:ltr">                    int nRelayNodes = fReachable ? 2 : 1; // limited relaying of addresses outside our network(s)</p>
<p style="Normal" xid="2588" props="text-align:left; dom-dir:ltr">                    for (multimap&lt;uint256, CNode*&gt;::iterator mi = mapMix.begin(); mi != mapMix.end() &amp;&amp; nRelayNodes-- &gt; 0; ++mi)</p>
<p style="Normal" xid="2589" props="text-align:left; dom-dir:ltr">                        ((*mi).second)-&gt;PushAddress(addr);</p>
<p style="Normal" xid="2590">                }</p>
<p style="Normal" xid="2591">            }</p>
<p style="Normal" xid="2592" props="text-align:left; dom-dir:ltr">            // Do not store addresses outside our network</p>
<p style="Normal" xid="2593" props="text-align:left; dom-dir:ltr">            if (fReachable)</p>
<p style="Normal" xid="2594" props="text-align:left; dom-dir:ltr">                vAddrOk.push_back(addr);</p>
<p style="Normal" xid="2595">        }</p>
<p style="Normal" xid="2596" props="text-align:left; dom-dir:ltr">        addrman.Add(vAddrOk, pfrom-&gt;addr, 2 * 60 * 60);</p>
<p style="Normal" xid="2597" props="text-align:left; dom-dir:ltr">        if (vAddr.size() &lt; 1000)</p>
<p style="Normal" xid="2598" props="text-align:left; dom-dir:ltr">            pfrom-&gt;fGetAddr = false;</p>
<p style="Normal" xid="2599" props="text-align:left; dom-dir:ltr">        if (pfrom-&gt;fOneShot)</p>
<p style="Normal" xid="2600" props="text-align:left; dom-dir:ltr">            pfrom-&gt;fDisconnect = true;</p>
<p style="Normal" xid="2601">    }</p>
<p style="Normal" xid="2602"><c></c></p>
<p style="Normal" xid="2603"><c></c></p>
<p style="Normal" xid="2604" props="text-align:left; dom-dir:ltr">    else if (strCommand == "inv")</p>
<p style="Normal" xid="2605">    {</p>
<p style="Normal" xid="2606" props="text-align:left; dom-dir:ltr">        vector&lt;CInv&gt; vInv;</p>
<p style="Normal" xid="2607" props="text-align:left; dom-dir:ltr">        vRecv &gt;&gt; vInv;</p>
<p style="Normal" xid="2608" props="text-align:left; dom-dir:ltr">        if (vInv.size() &gt; 50000)</p>
<p style="Normal" xid="2609">        {</p>
<p style="Normal" xid="2610" props="text-align:left; dom-dir:ltr">            pfrom-&gt;Misbehaving(20);</p>
<p style="Normal" xid="2611" props="text-align:left; dom-dir:ltr">            return error("message inv size() = %d", vInv.size());</p>
<p style="Normal" xid="2612">        }</p>
<p style="Normal" xid="2613"><c></c></p>
<p style="Normal" xid="2614" props="text-align:left; dom-dir:ltr">        // find last block in inv vector</p>
<p style="Normal" xid="2615" props="text-align:left; dom-dir:ltr">        unsigned int nLastBlock = (unsigned int)(-1);</p>
<p style="Normal" xid="2616" props="text-align:left; dom-dir:ltr">        for (unsigned int nInv = 0; nInv &lt; vInv.size(); nInv++) {</p>
<p style="Normal" xid="2617" props="text-align:left; dom-dir:ltr">            if (vInv[vInv.size() - 1 - nInv].type == MSG_BLOCK) {</p>
<p style="Normal" xid="2618" props="text-align:left; dom-dir:ltr">                nLastBlock = vInv.size() - 1 - nInv;</p>
<p style="Normal" xid="2619" props="text-align:left; dom-dir:ltr">                break;</p>
<p style="Normal" xid="2620">            }</p>
<p style="Normal" xid="2621">        }</p>
<p style="Normal" xid="2622" props="text-align:left; dom-dir:ltr">        CTxDB txdb("r");</p>
<p style="Normal" xid="2623" props="text-align:left; dom-dir:ltr">        for (unsigned int nInv = 0; nInv &lt; vInv.size(); nInv++)</p>
<p style="Normal" xid="2624">        {</p>
<p style="Normal" xid="2625" props="text-align:left; dom-dir:ltr">            const CInv &amp;inv = vInv[nInv];</p>
<p style="Normal" xid="2626"><c></c></p>
<p style="Normal" xid="2627" props="text-align:left; dom-dir:ltr">            if (fShutdown)</p>
<p style="Normal" xid="2628" props="text-align:left; dom-dir:ltr">                return true;</p>
<p style="Normal" xid="2629" props="text-align:left; dom-dir:ltr">            pfrom-&gt;AddInventoryKnown(inv);</p>
<p style="Normal" xid="2630"><c></c></p>
<p style="Normal" xid="2631" props="text-align:left; dom-dir:ltr">            bool fAlreadyHave = AlreadyHave(txdb, inv);</p>
<p style="Normal" xid="2632" props="text-align:left; dom-dir:ltr">            if (fDebug)</p>
<p style="Normal" xid="2633" props="text-align:left; dom-dir:ltr">                printf("  got inventory: %s  %s\n", inv.ToString().c_str(), fAlreadyHave ? "have" : "new");</p>
<p style="Normal" xid="2634"><c></c></p>
<p style="Normal" xid="2635" props="text-align:left; dom-dir:ltr">            if (!fAlreadyHave)</p>
<p style="Normal" xid="2636" props="text-align:left; dom-dir:ltr">                pfrom-&gt;AskFor(inv);</p>
<p style="Normal" xid="2637" props="text-align:left; dom-dir:ltr">            else if (inv.type == MSG_BLOCK &amp;&amp; mapOrphanBlocks.count(inv.hash)) {</p>
<p style="Normal" xid="2638" props="text-align:left; dom-dir:ltr">                pfrom-&gt;PushGetBlocks(pindexBest, GetOrphanRoot(mapOrphanBlocks[inv.hash]));</p>
<p style="Normal" xid="2639" props="text-align:left; dom-dir:ltr">            } else if (nInv == nLastBlock) {</p>
<p style="Normal" xid="2640" props="text-align:left; dom-dir:ltr">                // In case we are on a very long side-chain, it is possible that we already have</p>
<p style="Normal" xid="2641" props="text-align:left; dom-dir:ltr">                // the last block in an inv bundle sent in response to getblocks. Try to detect</p>
<p style="Normal" xid="2642" props="text-align:left; dom-dir:ltr">                // this situation and push another getblocks to continue.</p>
<p style="Normal" xid="2643" props="text-align:left; dom-dir:ltr">                std::vector&lt;CInv&gt; vGetData(1,inv);</p>
<p style="Normal" xid="2644" props="text-align:left; dom-dir:ltr">                pfrom-&gt;PushGetBlocks(mapBlockIndex[inv.hash], uint256(0));</p>
<p style="Normal" xid="2645" props="text-align:left; dom-dir:ltr">                if (fDebug)</p>
<p style="Normal" xid="2646" props="text-align:left; dom-dir:ltr">                    printf("force request: %s\n", inv.ToString().c_str());</p>
<p style="Normal" xid="2647">            }</p>
<p style="Normal" xid="2648"><c></c></p>
<p style="Normal" xid="2649" props="text-align:left; dom-dir:ltr">            // Track requests for our stuff</p>
<p style="Normal" xid="2650" props="text-align:left; dom-dir:ltr">            Inventory(inv.hash);</p>
<p style="Normal" xid="2651">        }</p>
<p style="Normal" xid="2652">    }</p>
<p style="Normal" xid="2653"><c></c></p>
<p style="Normal" xid="2654"><c></c></p>
<p style="Normal" xid="2655" props="text-align:left; dom-dir:ltr">    else if (strCommand == "getdata")</p>
<p style="Normal" xid="2656">    {</p>
<p style="Normal" xid="2657" props="text-align:left; dom-dir:ltr">        vector&lt;CInv&gt; vInv;</p>
<p style="Normal" xid="2658" props="text-align:left; dom-dir:ltr">        vRecv &gt;&gt; vInv;</p>
<p style="Normal" xid="2659" props="text-align:left; dom-dir:ltr">        if (vInv.size() &gt; 50000)</p>
<p style="Normal" xid="2660">        {</p>
<p style="Normal" xid="2661" props="text-align:left; dom-dir:ltr">            pfrom-&gt;Misbehaving(20);</p>
<p style="Normal" xid="2662" props="text-align:left; dom-dir:ltr">            return error("message getdata size() = %d", vInv.size());</p>
<p style="Normal" xid="2663">        }</p>
<p style="Normal" xid="2664"><c></c></p>
<p style="Normal" xid="2665" props="text-align:left; dom-dir:ltr">        if (fDebugNet || (vInv.size() != 1))</p>
<p style="Normal" xid="2666" props="text-align:left; dom-dir:ltr">            printf("received getdata (%d invsz)\n", vInv.size());</p>
<p style="Normal" xid="2667"><c></c></p>
<p style="Normal" xid="2668" props="text-align:left; dom-dir:ltr">        BOOST_FOREACH(const CInv&amp; inv, vInv)</p>
<p style="Normal" xid="2669">        {</p>
<p style="Normal" xid="2670" props="text-align:left; dom-dir:ltr">            if (fShutdown)</p>
<p style="Normal" xid="2671" props="text-align:left; dom-dir:ltr">                return true;</p>
<p style="Normal" xid="2672" props="text-align:left; dom-dir:ltr">            if (fDebugNet || (vInv.size() == 1))</p>
<p style="Normal" xid="2673" props="text-align:left; dom-dir:ltr">                printf("received getdata for: %s\n", inv.ToString().c_str());</p>
<p style="Normal" xid="2674"><c></c></p>
<p style="Normal" xid="2675" props="text-align:left; dom-dir:ltr">            if (inv.type == MSG_BLOCK)</p>
<p style="Normal" xid="2676">            {</p>
<p style="Normal" xid="2677" props="text-align:left; dom-dir:ltr">                // Send block from disk</p>
<p style="Normal" xid="2678" props="text-align:left; dom-dir:ltr">                map&lt;uint256, CBlockIndex*&gt;::iterator mi = mapBlockIndex.find(inv.hash);</p>
<p style="Normal" xid="2679" props="text-align:left; dom-dir:ltr">                if (mi != mapBlockIndex.end())</p>
<p style="Normal" xid="2680">                {</p>
<p style="Normal" xid="2681" props="text-align:left; dom-dir:ltr">                    CBlock block;</p>
<p style="Normal" xid="2682" props="text-align:left; dom-dir:ltr">                    block.ReadFromDisk((*mi).second);</p>
<p style="Normal" xid="2683" props="text-align:left; dom-dir:ltr">                    pfrom-&gt;PushMessage("block", block);</p>
<p style="Normal" xid="2684"><c></c></p>
<p style="Normal" xid="2685" props="text-align:left; dom-dir:ltr">                    // Trigger them to send a getblocks request for the next batch of inventory</p>
<p style="Normal" xid="2686" props="text-align:left; dom-dir:ltr">                    if (inv.hash == pfrom-&gt;hashContinue)</p>
<p style="Normal" xid="2687">                    {</p>
<p style="Normal" xid="2688" props="text-align:left; dom-dir:ltr">                        // Bypass PushInventory, this must send even if redundant,</p>
<p style="Normal" xid="2689" props="text-align:left; dom-dir:ltr">                        // and we want it right after the last block so they don't</p>
<p style="Normal" xid="2690" props="text-align:left; dom-dir:ltr">                        // wait for other stuff first.</p>
<p style="Normal" xid="2691" props="text-align:left; dom-dir:ltr">                        vector&lt;CInv&gt; vInv;</p>
<p style="Normal" xid="2692" props="text-align:left; dom-dir:ltr">                        vInv.push_back(CInv(MSG_BLOCK, hashBestChain));</p>
<p style="Normal" xid="2693" props="text-align:left; dom-dir:ltr">                        pfrom-&gt;PushMessage("inv", vInv);</p>
<p style="Normal" xid="2694" props="text-align:left; dom-dir:ltr">                        pfrom-&gt;hashContinue = 0;</p>
<p style="Normal" xid="2695">                    }</p>
<p style="Normal" xid="2696">                }</p>
<p style="Normal" xid="2697">            }</p>
<p style="Normal" xid="2698" props="text-align:left; dom-dir:ltr">            else if (inv.IsKnownType())</p>
<p style="Normal" xid="2699">            {</p>
<p style="Normal" xid="2700" props="text-align:left; dom-dir:ltr">                // Send stream from relay memory</p>
<p style="Normal" xid="2701">                {</p>
<p style="Normal" xid="2702" props="text-align:left; dom-dir:ltr">                    LOCK(cs_mapRelay);</p>
<p style="Normal" xid="2703" props="text-align:left; dom-dir:ltr">                    map&lt;CInv, CDataStream&gt;::iterator mi = mapRelay.find(inv);</p>
<p style="Normal" xid="2704" props="text-align:left; dom-dir:ltr">                    if (mi != mapRelay.end())</p>
<p style="Normal" xid="2705" props="text-align:left; dom-dir:ltr">                        pfrom-&gt;PushMessage(inv.GetCommand(), (*mi).second);</p>
<p style="Normal" xid="2706">                }</p>
<p style="Normal" xid="2707">            }</p>
<p style="Normal" xid="2708"><c></c></p>
<p style="Normal" xid="2709" props="text-align:left; dom-dir:ltr">            // Track requests for our stuff</p>
<p style="Normal" xid="2710" props="text-align:left; dom-dir:ltr">            Inventory(inv.hash);</p>
<p style="Normal" xid="2711">        }</p>
<p style="Normal" xid="2712">    }</p>
<p style="Normal" xid="2713"><c></c></p>
<p style="Normal" xid="2714"><c></c></p>
<p style="Normal" xid="2715" props="text-align:left; dom-dir:ltr">    else if (strCommand == "getblocks")</p>
<p style="Normal" xid="2716">    {</p>
<p style="Normal" xid="2717" props="text-align:left; dom-dir:ltr">        CBlockLocator locator;</p>
<p style="Normal" xid="2718" props="text-align:left; dom-dir:ltr">        uint256 hashStop;</p>
<p style="Normal" xid="2719" props="text-align:left; dom-dir:ltr">        vRecv &gt;&gt; locator &gt;&gt; hashStop;</p>
<p style="Normal" xid="2720"><c></c></p>
<p style="Normal" xid="2721" props="text-align:left; dom-dir:ltr">        // Find the last block the caller has in the main chain</p>
<p style="Normal" xid="2722" props="text-align:left; dom-dir:ltr">        CBlockIndex* pindex = locator.GetBlockIndex();</p>
<p style="Normal" xid="2723"><c></c></p>
<p style="Normal" xid="2724" props="text-align:left; dom-dir:ltr">        // Send the rest of the chain</p>
<p style="Normal" xid="2725" props="text-align:left; dom-dir:ltr">        if (pindex)</p>
<p style="Normal" xid="2726" props="text-align:left; dom-dir:ltr">            pindex = pindex-&gt;pnext;</p>
<p style="Normal" xid="2727" props="text-align:left; dom-dir:ltr">        int nLimit = 500;</p>
<p style="Normal" xid="2728" props="text-align:left; dom-dir:ltr">        printf("getblocks %d to %s limit %d\n", (pindex ? pindex-&gt;nHeight : -1), hashStop.ToString().substr(0,20).c_str(), nLimit);</p>
<p style="Normal" xid="2729" props="text-align:left; dom-dir:ltr">        for (; pindex; pindex = pindex-&gt;pnext)</p>
<p style="Normal" xid="2730">        {</p>
<p style="Normal" xid="2731" props="text-align:left; dom-dir:ltr">            if (pindex-&gt;GetBlockHash() == hashStop)</p>
<p style="Normal" xid="2732">            {</p>
<p style="Normal" xid="2733" props="text-align:left; dom-dir:ltr">                printf("  getblocks stopping at %d %s\n", pindex-&gt;nHeight, pindex-&gt;GetBlockHash().ToString().substr(0,20).c_str());</p>
<p style="Normal" xid="2734" props="text-align:left; dom-dir:ltr">                break;</p>
<p style="Normal" xid="2735">            }</p>
<p style="Normal" xid="2736" props="text-align:left; dom-dir:ltr">            pfrom-&gt;PushInventory(CInv(MSG_BLOCK, pindex-&gt;GetBlockHash()));</p>
<p style="Normal" xid="2737" props="text-align:left; dom-dir:ltr">            if (--nLimit &lt;= 0)</p>
<p style="Normal" xid="2738">            {</p>
<p style="Normal" xid="2739" props="text-align:left; dom-dir:ltr">                // When this block is requested, we'll send an inv that'll make them</p>
<p style="Normal" xid="2740" props="text-align:left; dom-dir:ltr">                // getblocks the next batch of inventory.</p>
<p style="Normal" xid="2741" props="text-align:left; dom-dir:ltr">                printf("  getblocks stopping at limit %d %s\n", pindex-&gt;nHeight, pindex-&gt;GetBlockHash().ToString().substr(0,20).c_str());</p>
<p style="Normal" xid="2742" props="text-align:left; dom-dir:ltr">                pfrom-&gt;hashContinue = pindex-&gt;GetBlockHash();</p>
<p style="Normal" xid="2743" props="text-align:left; dom-dir:ltr">                break;</p>
<p style="Normal" xid="2744">            }</p>
<p style="Normal" xid="2745">        }</p>
<p style="Normal" xid="2746">    }</p>
<p style="Normal" xid="2747"><c></c></p>
<p style="Normal" xid="2748"><c></c></p>
<p style="Normal" xid="2749" props="text-align:left; dom-dir:ltr">    else if (strCommand == "getheaders")</p>
<p style="Normal" xid="2750">    {</p>
<p style="Normal" xid="2751" props="text-align:left; dom-dir:ltr">        CBlockLocator locator;</p>
<p style="Normal" xid="2752" props="text-align:left; dom-dir:ltr">        uint256 hashStop;</p>
<p style="Normal" xid="2753" props="text-align:left; dom-dir:ltr">        vRecv &gt;&gt; locator &gt;&gt; hashStop;</p>
<p style="Normal" xid="2754"><c></c></p>
<p style="Normal" xid="2755" props="text-align:left; dom-dir:ltr">        CBlockIndex* pindex = NULL;</p>
<p style="Normal" xid="2756" props="text-align:left; dom-dir:ltr">        if (locator.IsNull())</p>
<p style="Normal" xid="2757">        {</p>
<p style="Normal" xid="2758" props="text-align:left; dom-dir:ltr">            // If locator is null, return the hashStop block</p>
<p style="Normal" xid="2759" props="text-align:left; dom-dir:ltr">            map&lt;uint256, CBlockIndex*&gt;::iterator mi = mapBlockIndex.find(hashStop);</p>
<p style="Normal" xid="2760" props="text-align:left; dom-dir:ltr">            if (mi == mapBlockIndex.end())</p>
<p style="Normal" xid="2761" props="text-align:left; dom-dir:ltr">                return true;</p>
<p style="Normal" xid="2762" props="text-align:left; dom-dir:ltr">            pindex = (*mi).second;</p>
<p style="Normal" xid="2763">        }</p>
<p style="Normal" xid="2764" props="text-align:left; dom-dir:ltr">        else</p>
<p style="Normal" xid="2765">        {</p>
<p style="Normal" xid="2766" props="text-align:left; dom-dir:ltr">            // Find the last block the caller has in the main chain</p>
<p style="Normal" xid="2767" props="text-align:left; dom-dir:ltr">            pindex = locator.GetBlockIndex();</p>
<p style="Normal" xid="2768" props="text-align:left; dom-dir:ltr">            if (pindex)</p>
<p style="Normal" xid="2769" props="text-align:left; dom-dir:ltr">                pindex = pindex-&gt;pnext;</p>
<p style="Normal" xid="2770">        }</p>
<p style="Normal" xid="2771"><c></c></p>
<p style="Normal" xid="2772" props="text-align:left; dom-dir:ltr">        vector&lt;CBlock&gt; vHeaders;</p>
<p style="Normal" xid="2773" props="text-align:left; dom-dir:ltr">        int nLimit = 2000;</p>
<p style="Normal" xid="2774" props="text-align:left; dom-dir:ltr">        printf("getheaders %d to %s\n", (pindex ? pindex-&gt;nHeight : -1), hashStop.ToString().substr(0,20).c_str());</p>
<p style="Normal" xid="2775" props="text-align:left; dom-dir:ltr">        for (; pindex; pindex = pindex-&gt;pnext)</p>
<p style="Normal" xid="2776">        {</p>
<p style="Normal" xid="2777" props="text-align:left; dom-dir:ltr">            vHeaders.push_back(pindex-&gt;GetBlockHeader());</p>
<p style="Normal" xid="2778" props="text-align:left; dom-dir:ltr">            if (--nLimit &lt;= 0 || pindex-&gt;GetBlockHash() == hashStop)</p>
<p style="Normal" xid="2779" props="text-align:left; dom-dir:ltr">                break;</p>
<p style="Normal" xid="2780">        }</p>
<p style="Normal" xid="2781" props="text-align:left; dom-dir:ltr">        pfrom-&gt;PushMessage("headers", vHeaders);</p>
<p style="Normal" xid="2782">    }</p>
<p style="Normal" xid="2783"><c></c></p>
<p style="Normal" xid="2784"><c></c></p>
<p style="Normal" xid="2785" props="text-align:left; dom-dir:ltr">    else if (strCommand == "tx")</p>
<p style="Normal" xid="2786">    {</p>
<p style="Normal" xid="2787" props="text-align:left; dom-dir:ltr">        vector&lt;uint256&gt; vWorkQueue;</p>
<p style="Normal" xid="2788" props="text-align:left; dom-dir:ltr">        vector&lt;uint256&gt; vEraseQueue;</p>
<p style="Normal" xid="2789" props="text-align:left; dom-dir:ltr">        CDataStream vMsg(vRecv);</p>
<p style="Normal" xid="2790" props="text-align:left; dom-dir:ltr">        CTxDB txdb("r");</p>
<p style="Normal" xid="2791" props="text-align:left; dom-dir:ltr">        CTransaction tx;</p>
<p style="Normal" xid="2792" props="text-align:left; dom-dir:ltr">        vRecv &gt;&gt; tx;</p>
<p style="Normal" xid="2793"><c></c></p>
<p style="Normal" xid="2794" props="text-align:left; dom-dir:ltr">        CInv inv(MSG_TX, tx.GetHash());</p>
<p style="Normal" xid="2795" props="text-align:left; dom-dir:ltr">        pfrom-&gt;AddInventoryKnown(inv);</p>
<p style="Normal" xid="2796"><c></c></p>
<p style="Normal" xid="2797" props="text-align:left; dom-dir:ltr">        bool fMissingInputs = false;</p>
<p style="Normal" xid="2798" props="text-align:left; dom-dir:ltr">        if (tx.AcceptToMemoryPool(txdb, true, &amp;fMissingInputs))</p>
<p style="Normal" xid="2799">        {</p>
<p style="Normal" xid="2800" props="text-align:left; dom-dir:ltr">            SyncWithWallets(tx, NULL, true);</p>
<p style="Normal" xid="2801" props="text-align:left; dom-dir:ltr">            RelayMessage(inv, vMsg);</p>
<p style="Normal" xid="2802" props="text-align:left; dom-dir:ltr">            mapAlreadyAskedFor.erase(inv);</p>
<p style="Normal" xid="2803" props="text-align:left; dom-dir:ltr">            vWorkQueue.push_back(inv.hash);</p>
<p style="Normal" xid="2804" props="text-align:left; dom-dir:ltr">            vEraseQueue.push_back(inv.hash);</p>
<p style="Normal" xid="2805"><c></c></p>
<p style="Normal" xid="2806" props="text-align:left; dom-dir:ltr">            // Recursively process any orphan transactions that depended on this one</p>
<p style="Normal" xid="2807" props="text-align:left; dom-dir:ltr">            for (unsigned int i = 0; i &lt; vWorkQueue.size(); i++)</p>
<p style="Normal" xid="2808">            {</p>
<p style="Normal" xid="2809" props="text-align:left; dom-dir:ltr">                uint256 hashPrev = vWorkQueue[i];</p>
<p style="Normal" xid="2810" props="text-align:left; dom-dir:ltr">                for (map&lt;uint256, CDataStream*&gt;::iterator mi = mapOrphanTransactionsByPrev[hashPrev].begin();</p>
<p style="Normal" xid="2811" props="text-align:left; dom-dir:ltr">                     mi != mapOrphanTransactionsByPrev[hashPrev].end();</p>
<p style="Normal" xid="2812" props="text-align:left; dom-dir:ltr">                     ++mi)</p>
<p style="Normal" xid="2813">                {</p>
<p style="Normal" xid="2814" props="text-align:left; dom-dir:ltr">                    const CDataStream&amp; vMsg = *((*mi).second);</p>
<p style="Normal" xid="2815" props="text-align:left; dom-dir:ltr">                    CTransaction tx;</p>
<p style="Normal" xid="2816" props="text-align:left; dom-dir:ltr">                    CDataStream(vMsg) &gt;&gt; tx;</p>
<p style="Normal" xid="2817" props="text-align:left; dom-dir:ltr">                    CInv inv(MSG_TX, tx.GetHash());</p>
<p style="Normal" xid="2818" props="text-align:left; dom-dir:ltr">                    bool fMissingInputs2 = false;</p>
<p style="Normal" xid="2819"><c></c></p>
<p style="Normal" xid="2820" props="text-align:left; dom-dir:ltr">                    if (tx.AcceptToMemoryPool(txdb, true, &amp;fMissingInputs2))</p>
<p style="Normal" xid="2821">                    {</p>
<p style="Normal" xid="2822" props="text-align:left; dom-dir:ltr">                        printf("   accepted orphan tx %s\n", inv.hash.ToString().substr(0,10).c_str());</p>
<p style="Normal" xid="2823" props="text-align:left; dom-dir:ltr">                        SyncWithWallets(tx, NULL, true);</p>
<p style="Normal" xid="2824" props="text-align:left; dom-dir:ltr">                        RelayMessage(inv, vMsg);</p>
<p style="Normal" xid="2825" props="text-align:left; dom-dir:ltr">                        mapAlreadyAskedFor.erase(inv);</p>
<p style="Normal" xid="2826" props="text-align:left; dom-dir:ltr">                        vWorkQueue.push_back(inv.hash);</p>
<p style="Normal" xid="2827" props="text-align:left; dom-dir:ltr">                        vEraseQueue.push_back(inv.hash);</p>
<p style="Normal" xid="2828">                    }</p>
<p style="Normal" xid="2829" props="text-align:left; dom-dir:ltr">                    else if (!fMissingInputs2)</p>
<p style="Normal" xid="2830">                    {</p>
<p style="Normal" xid="2831" props="text-align:left; dom-dir:ltr">                        // invalid orphan</p>
<p style="Normal" xid="2832" props="text-align:left; dom-dir:ltr">                        vEraseQueue.push_back(inv.hash);</p>
<p style="Normal" xid="2833" props="text-align:left; dom-dir:ltr">                        printf("   removed invalid orphan tx %s\n", inv.hash.ToString().substr(0,10).c_str());</p>
<p style="Normal" xid="2834">                    }</p>
<p style="Normal" xid="2835">                }</p>
<p style="Normal" xid="2836">            }</p>
<p style="Normal" xid="2837"><c></c></p>
<p style="Normal" xid="2838" props="text-align:left; dom-dir:ltr">            BOOST_FOREACH(uint256 hash, vEraseQueue)</p>
<p style="Normal" xid="2839" props="text-align:left; dom-dir:ltr">                EraseOrphanTx(hash);</p>
<p style="Normal" xid="2840">        }</p>
<p style="Normal" xid="2841" props="text-align:left; dom-dir:ltr">        else if (fMissingInputs)</p>
<p style="Normal" xid="2842">        {</p>
<p style="Normal" xid="2843" props="text-align:left; dom-dir:ltr">            AddOrphanTx(vMsg);</p>
<p style="Normal" xid="2844"><c></c></p>
<p style="Normal" xid="2845" props="text-align:left; dom-dir:ltr">            // DoS prevention: do not allow mapOrphanTransactions to grow unbounded</p>
<p style="Normal" xid="2846" props="text-align:left; dom-dir:ltr">            unsigned int nEvicted = LimitOrphanTxSize(MAX_ORPHAN_TRANSACTIONS);</p>
<p style="Normal" xid="2847" props="text-align:left; dom-dir:ltr">            if (nEvicted &gt; 0)</p>
<p style="Normal" xid="2848" props="text-align:left; dom-dir:ltr">                printf("mapOrphan overflow, removed %u tx\n", nEvicted);</p>
<p style="Normal" xid="2849">        }</p>
<p style="Normal" xid="2850" props="text-align:left; dom-dir:ltr">        if (tx.nDoS) pfrom-&gt;Misbehaving(tx.nDoS);</p>
<p style="Normal" xid="2851">    }</p>
<p style="Normal" xid="2852"><c></c></p>
<p style="Normal" xid="2853"><c></c></p>
<p style="Normal" xid="2854" props="text-align:left; dom-dir:ltr">    else if (strCommand == "block")</p>
<p style="Normal" xid="2855">    {</p>
<p style="Normal" xid="2856" props="text-align:left; dom-dir:ltr">        CBlock block;</p>
<p style="Normal" xid="2857" props="text-align:left; dom-dir:ltr">        vRecv &gt;&gt; block;</p>
<p style="Normal" xid="2858"><c></c></p>
<p style="Normal" xid="2859" props="text-align:left; dom-dir:ltr">        printf("received block %s\n", block.GetHash().ToString().substr(0,20).c_str());</p>
<p style="Normal" xid="2860" props="text-align:left; dom-dir:ltr">        // block.print();</p>
<p style="Normal" xid="2861"><c></c></p>
<p style="Normal" xid="2862" props="text-align:left; dom-dir:ltr">        CInv inv(MSG_BLOCK, block.GetHash());</p>
<p style="Normal" xid="2863" props="text-align:left; dom-dir:ltr">        pfrom-&gt;AddInventoryKnown(inv);</p>
<p style="Normal" xid="2864"><c></c></p>
<p style="Normal" xid="2865" props="text-align:left; dom-dir:ltr">        if (ProcessBlock(pfrom, &amp;block))</p>
<p style="Normal" xid="2866" props="text-align:left; dom-dir:ltr">            mapAlreadyAskedFor.erase(inv);</p>
<p style="Normal" xid="2867" props="text-align:left; dom-dir:ltr">        if (block.nDoS) pfrom-&gt;Misbehaving(block.nDoS);</p>
<p style="Normal" xid="2868">    }</p>
<p style="Normal" xid="2869"><c></c></p>
<p style="Normal" xid="2870"><c></c></p>
<p style="Normal" xid="2871" props="text-align:left; dom-dir:ltr">    else if (strCommand == "getaddr")</p>
<p style="Normal" xid="2872">    {</p>
<p style="Normal" xid="2873" props="text-align:left; dom-dir:ltr">        pfrom-&gt;vAddrToSend.clear();</p>
<p style="Normal" xid="2874" props="text-align:left; dom-dir:ltr">        vector&lt;CAddress&gt; vAddr = addrman.GetAddr();</p>
<p style="Normal" xid="2875" props="text-align:left; dom-dir:ltr">        BOOST_FOREACH(const CAddress &amp;addr, vAddr)</p>
<p style="Normal" xid="2876" props="text-align:left; dom-dir:ltr">            pfrom-&gt;PushAddress(addr);</p>
<p style="Normal" xid="2877">    }</p>
<p style="Normal" xid="2878"><c></c></p>
<p style="Normal" xid="2879"><c></c></p>
<p style="Normal" xid="2880" props="text-align:left; dom-dir:ltr">    else if (strCommand == "checkorder")</p>
<p style="Normal" xid="2881">    {</p>
<p style="Normal" xid="2882" props="text-align:left; dom-dir:ltr">        uint256 hashReply;</p>
<p style="Normal" xid="2883" props="text-align:left; dom-dir:ltr">        vRecv &gt;&gt; hashReply;</p>
<p style="Normal" xid="2884"><c></c></p>
<p style="Normal" xid="2885" props="text-align:left; dom-dir:ltr">        if (!GetBoolArg("-allowreceivebyip"))</p>
<p style="Normal" xid="2886">        {</p>
<p style="Normal" xid="2887" props="text-align:left; dom-dir:ltr">            pfrom-&gt;PushMessage("reply", hashReply, (int)2, string(""));</p>
<p style="Normal" xid="2888" props="text-align:left; dom-dir:ltr">            return true;</p>
<p style="Normal" xid="2889">        }</p>
<p style="Normal" xid="2890"><c></c></p>
<p style="Normal" xid="2891" props="text-align:left; dom-dir:ltr">        CWalletTx order;</p>
<p style="Normal" xid="2892" props="text-align:left; dom-dir:ltr">        vRecv &gt;&gt; order;</p>
<p style="Normal" xid="2893"><c></c></p>
<p style="Normal" xid="2894" props="text-align:left; dom-dir:ltr">        /// we have a chance to check the order here</p>
<p style="Normal" xid="2895"><c></c></p>
<p style="Normal" xid="2896" props="text-align:left; dom-dir:ltr">        // Keep giving the same key to the same ip until they use it</p>
<p style="Normal" xid="2897" props="text-align:left; dom-dir:ltr">        if (!mapReuseKey.count(pfrom-&gt;addr))</p>
<p style="Normal" xid="2898" props="text-align:left; dom-dir:ltr">            pwalletMain-&gt;GetKeyFromPool(mapReuseKey[pfrom-&gt;addr], true);</p>
<p style="Normal" xid="2899"><c></c></p>
<p style="Normal" xid="2900" props="text-align:left; dom-dir:ltr">        // Send back approval of order and pubkey to use</p>
<p style="Normal" xid="2901" props="text-align:left; dom-dir:ltr">        CScript scriptPubKey;</p>
<p style="Normal" xid="2902" props="text-align:left; dom-dir:ltr">        scriptPubKey &lt;&lt; mapReuseKey[pfrom-&gt;addr] &lt;&lt; OP_CHECKSIG;</p>
<p style="Normal" xid="2903" props="text-align:left; dom-dir:ltr">        pfrom-&gt;PushMessage("reply", hashReply, (int)0, scriptPubKey);</p>
<p style="Normal" xid="2904">    }</p>
<p style="Normal" xid="2905"><c></c></p>
<p style="Normal" xid="2906"><c></c></p>
<p style="Normal" xid="2907" props="text-align:left; dom-dir:ltr">    else if (strCommand == "reply")</p>
<p style="Normal" xid="2908">    {</p>
<p style="Normal" xid="2909" props="text-align:left; dom-dir:ltr">        uint256 hashReply;</p>
<p style="Normal" xid="2910" props="text-align:left; dom-dir:ltr">        vRecv &gt;&gt; hashReply;</p>
<p style="Normal" xid="2911"><c></c></p>
<p style="Normal" xid="2912" props="text-align:left; dom-dir:ltr">        CRequestTracker tracker;</p>
<p style="Normal" xid="2913">        {</p>
<p style="Normal" xid="2914" props="text-align:left; dom-dir:ltr">            LOCK(pfrom-&gt;cs_mapRequests);</p>
<p style="Normal" xid="2915" props="text-align:left; dom-dir:ltr">            map&lt;uint256, CRequestTracker&gt;::iterator mi = pfrom-&gt;mapRequests.find(hashReply);</p>
<p style="Normal" xid="2916" props="text-align:left; dom-dir:ltr">            if (mi != pfrom-&gt;mapRequests.end())</p>
<p style="Normal" xid="2917">            {</p>
<p style="Normal" xid="2918" props="text-align:left; dom-dir:ltr">                tracker = (*mi).second;</p>
<p style="Normal" xid="2919" props="text-align:left; dom-dir:ltr">                pfrom-&gt;mapRequests.erase(mi);</p>
<p style="Normal" xid="2920">            }</p>
<p style="Normal" xid="2921">        }</p>
<p style="Normal" xid="2922" props="text-align:left; dom-dir:ltr">        if (!tracker.IsNull())</p>
<p style="Normal" xid="2923" props="text-align:left; dom-dir:ltr">            tracker.fn(tracker.param1, vRecv);</p>
<p style="Normal" xid="2924">    }</p>
<p style="Normal" xid="2925"><c></c></p>
<p style="Normal" xid="2926"><c></c></p>
<p style="Normal" xid="2927" props="text-align:left; dom-dir:ltr">    else if (strCommand == "ping")</p>
<p style="Normal" xid="2928">    {</p>
<p style="Normal" xid="2929" props="text-align:left; dom-dir:ltr">        if (pfrom-&gt;nVersion &gt; BIP0031_VERSION)</p>
<p style="Normal" xid="2930">        {</p>
<p style="Normal" xid="2931" props="text-align:left; dom-dir:ltr">            uint64 nonce = 0;</p>
<p style="Normal" xid="2932" props="text-align:left; dom-dir:ltr">            vRecv &gt;&gt; nonce;</p>
<p style="Normal" xid="2933" props="text-align:left; dom-dir:ltr">            // Echo the message back with the nonce. This allows for two useful features:</p>
<p style="Normal" xid="2934">            //</p>
<p style="Normal" xid="2935" props="text-align:left; dom-dir:ltr">            // 1) A remote node can quickly check if the connection is operational</p>
<p style="Normal" xid="2936" props="text-align:left; dom-dir:ltr">            // 2) Remote nodes can measure the latency of the network thread. If this node</p>
<p style="Normal" xid="2937" props="text-align:left; dom-dir:ltr">            //    is overloaded it won't respond to pings quickly and the remote node can</p>
<p style="Normal" xid="2938" props="text-align:left; dom-dir:ltr">            //    avoid sending us more work, like chain download requests.</p>
<p style="Normal" xid="2939">            //</p>
<p style="Normal" xid="2940" props="text-align:left; dom-dir:ltr">            // The nonce stops the remote getting confused between different pings: without</p>
<p style="Normal" xid="2941" props="text-align:left; dom-dir:ltr">            // it, if the remote node sends a ping once per second and this node takes 5</p>
<p style="Normal" xid="2942" props="text-align:left; dom-dir:ltr">            // seconds to respond to each, the 5th ping the remote sends would appear to</p>
<p style="Normal" xid="2943" props="text-align:left; dom-dir:ltr">            // return very quickly.</p>
<p style="Normal" xid="2944" props="text-align:left; dom-dir:ltr">            pfrom-&gt;PushMessage("pong", nonce);</p>
<p style="Normal" xid="2945">        }</p>
<p style="Normal" xid="2946">    }</p>
<p style="Normal" xid="2947"><c></c></p>
<p style="Normal" xid="2948"><c></c></p>
<p style="Normal" xid="2949" props="text-align:left; dom-dir:ltr">    else if (strCommand == "alert")</p>
<p style="Normal" xid="2950">    {</p>
<p style="Normal" xid="2951" props="text-align:left; dom-dir:ltr">        CAlert alert;</p>
<p style="Normal" xid="2952" props="text-align:left; dom-dir:ltr">        vRecv &gt;&gt; alert;</p>
<p style="Normal" xid="2953"><c></c></p>
<p style="Normal" xid="2954" props="text-align:left; dom-dir:ltr">        if (alert.ProcessAlert())</p>
<p style="Normal" xid="2955">        {</p>
<p style="Normal" xid="2956" props="text-align:left; dom-dir:ltr">            // Relay</p>
<p style="Normal" xid="2957" props="text-align:left; dom-dir:ltr">            pfrom-&gt;setKnown.insert(alert.GetHash());</p>
<p style="Normal" xid="2958">            {</p>
<p style="Normal" xid="2959" props="text-align:left; dom-dir:ltr">                LOCK(cs_vNodes);</p>
<p style="Normal" xid="2960" props="text-align:left; dom-dir:ltr">                BOOST_FOREACH(CNode* pnode, vNodes)</p>
<p style="Normal" xid="2961" props="text-align:left; dom-dir:ltr">                    alert.RelayTo(pnode);</p>
<p style="Normal" xid="2962">            }</p>
<p style="Normal" xid="2963">        }</p>
<p style="Normal" xid="2964">    }</p>
<p style="Normal" xid="2965"><c></c></p>
<p style="Normal" xid="2966"><c></c></p>
<p style="Normal" xid="2967" props="text-align:left; dom-dir:ltr">    else</p>
<p style="Normal" xid="2968">    {</p>
<p style="Normal" xid="2969" props="text-align:left; dom-dir:ltr">        // Ignore unknown commands for extensibility</p>
<p style="Normal" xid="2970">    }</p>
<p style="Normal" xid="2971"><c></c></p>
<p style="Normal" xid="2972"><c></c></p>
<p style="Normal" xid="2973" props="text-align:left; dom-dir:ltr">    // Update the last seen time for this node's address</p>
<p style="Normal" xid="2974" props="text-align:left; dom-dir:ltr">    if (pfrom-&gt;fNetworkNode)</p>
<p style="Normal" xid="2975" props="text-align:left; dom-dir:ltr">        if (strCommand == "version" || strCommand == "addr" || strCommand == "inv" || strCommand == "getdata" || strCommand == "ping")</p>
<p style="Normal" xid="2976" props="text-align:left; dom-dir:ltr">            AddressCurrentlyConnected(pfrom-&gt;addr);</p>
<p style="Normal" xid="2977"><c></c></p>
<p style="Normal" xid="2978"><c></c></p>
<p style="Normal" xid="2979" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="2980">}</p>
<p style="Normal" xid="2981"><c></c></p>
<p style="Normal" xid="2982" props="text-align:left; dom-dir:ltr">bool ProcessMessages(CNode* pfrom)</p>
<p style="Normal" xid="2983">{</p>
<p style="Normal" xid="2984" props="text-align:left; dom-dir:ltr">    CDataStream&amp; vRecv = pfrom-&gt;vRecv;</p>
<p style="Normal" xid="2985" props="text-align:left; dom-dir:ltr">    if (vRecv.empty())</p>
<p style="Normal" xid="2986" props="text-align:left; dom-dir:ltr">        return true;</p>
<p style="Normal" xid="2987" props="text-align:left; dom-dir:ltr">    //if (fDebug)</p>
<p style="Normal" xid="2988" props="text-align:left; dom-dir:ltr">    //    printf("ProcessMessages(%u bytes)\n", vRecv.size());</p>
<p style="Normal" xid="2989"><c></c></p>
<p style="Normal" xid="2990">    //</p>
<p style="Normal" xid="2991" props="text-align:left; dom-dir:ltr">    // Message format</p>
<p style="Normal" xid="2992" props="text-align:left; dom-dir:ltr">    //  (4) message start</p>
<p style="Normal" xid="2993" props="text-align:left; dom-dir:ltr">    //  (12) command</p>
<p style="Normal" xid="2994" props="text-align:left; dom-dir:ltr">    //  (4) size</p>
<p style="Normal" xid="2995" props="text-align:left; dom-dir:ltr">    //  (4) checksum</p>
<p style="Normal" xid="2996" props="text-align:left; dom-dir:ltr">    //  (x) data</p>
<p style="Normal" xid="2997">    //</p>
<p style="Normal" xid="2998"><c></c></p>
<p style="Normal" xid="2999" props="text-align:left; dom-dir:ltr">    loop</p>
<p style="Normal" xid="3000">    {</p>
<p style="Normal" xid="3001" props="text-align:left; dom-dir:ltr">        // Don't bother if send buffer is too full to respond anyway</p>
<p style="Normal" xid="3002" props="text-align:left; dom-dir:ltr">        if (pfrom-&gt;vSend.size() &gt;= SendBufferSize())</p>
<p style="Normal" xid="3003" props="text-align:left; dom-dir:ltr">            break;</p>
<p style="Normal" xid="3004"><c></c></p>
<p style="Normal" xid="3005" props="text-align:left; dom-dir:ltr">        // Scan for message start</p>
<p style="Normal" xid="3006" props="text-align:left; dom-dir:ltr">        CDataStream::iterator pstart = search(vRecv.begin(), vRecv.end(), BEGIN(pchMessageStart), END(pchMessageStart));</p>
<p style="Normal" xid="3007" props="text-align:left; dom-dir:ltr">        int nHeaderSize = vRecv.GetSerializeSize(CMessageHeader());</p>
<p style="Normal" xid="3008" props="text-align:left; dom-dir:ltr">        if (vRecv.end() - pstart &lt; nHeaderSize)</p>
<p style="Normal" xid="3009">        {</p>
<p style="Normal" xid="3010" props="text-align:left; dom-dir:ltr">            if ((int)vRecv.size() &gt; nHeaderSize)</p>
<p style="Normal" xid="3011">            {</p>
<p style="Normal" xid="3012" props="text-align:left; dom-dir:ltr">                printf("\n\nPROCESSMESSAGE MESSAGESTART NOT FOUND\n\n");</p>
<p style="Normal" xid="3013" props="text-align:left; dom-dir:ltr">                vRecv.erase(vRecv.begin(), vRecv.end() - nHeaderSize);</p>
<p style="Normal" xid="3014">            }</p>
<p style="Normal" xid="3015" props="text-align:left; dom-dir:ltr">            break;</p>
<p style="Normal" xid="3016">        }</p>
<p style="Normal" xid="3017" props="text-align:left; dom-dir:ltr">        if (pstart - vRecv.begin() &gt; 0)</p>
<p style="Normal" xid="3018" props="text-align:left; dom-dir:ltr">            printf("\n\nPROCESSMESSAGE SKIPPED %d BYTES\n\n", pstart - vRecv.begin());</p>
<p style="Normal" xid="3019" props="text-align:left; dom-dir:ltr">        vRecv.erase(vRecv.begin(), pstart);</p>
<p style="Normal" xid="3020"><c></c></p>
<p style="Normal" xid="3021" props="text-align:left; dom-dir:ltr">        // Read header</p>
<p style="Normal" xid="3022" props="text-align:left; dom-dir:ltr">        vector&lt;char&gt; vHeaderSave(vRecv.begin(), vRecv.begin() + nHeaderSize);</p>
<p style="Normal" xid="3023" props="text-align:left; dom-dir:ltr">        CMessageHeader hdr;</p>
<p style="Normal" xid="3024" props="text-align:left; dom-dir:ltr">        vRecv &gt;&gt; hdr;</p>
<p style="Normal" xid="3025" props="text-align:left; dom-dir:ltr">        if (!hdr.IsValid())</p>
<p style="Normal" xid="3026">        {</p>
<p style="Normal" xid="3027" props="text-align:left; dom-dir:ltr">            printf("\n\nPROCESSMESSAGE: ERRORS IN HEADER %s\n\n\n", hdr.GetCommand().c_str());</p>
<p style="Normal" xid="3028" props="text-align:left; dom-dir:ltr">            continue;</p>
<p style="Normal" xid="3029">        }</p>
<p style="Normal" xid="3030" props="text-align:left; dom-dir:ltr">        string strCommand = hdr.GetCommand();</p>
<p style="Normal" xid="3031"><c></c></p>
<p style="Normal" xid="3032" props="text-align:left; dom-dir:ltr">        // Message size</p>
<p style="Normal" xid="3033" props="text-align:left; dom-dir:ltr">        unsigned int nMessageSize = hdr.nMessageSize;</p>
<p style="Normal" xid="3034" props="text-align:left; dom-dir:ltr">        if (nMessageSize &gt; MAX_SIZE)</p>
<p style="Normal" xid="3035">        {</p>
<p style="Normal" xid="3036" props="text-align:left; dom-dir:ltr">            printf("ProcessMessages(%s, %u bytes) : nMessageSize &gt; MAX_SIZE\n", strCommand.c_str(), nMessageSize);</p>
<p style="Normal" xid="3037" props="text-align:left; dom-dir:ltr">            continue;</p>
<p style="Normal" xid="3038">        }</p>
<p style="Normal" xid="3039" props="text-align:left; dom-dir:ltr">        if (nMessageSize &gt; vRecv.size())</p>
<p style="Normal" xid="3040">        {</p>
<p style="Normal" xid="3041" props="text-align:left; dom-dir:ltr">            // Rewind and wait for rest of message</p>
<p style="Normal" xid="3042" props="text-align:left; dom-dir:ltr">            vRecv.insert(vRecv.begin(), vHeaderSave.begin(), vHeaderSave.end());</p>
<p style="Normal" xid="3043" props="text-align:left; dom-dir:ltr">            break;</p>
<p style="Normal" xid="3044">        }</p>
<p style="Normal" xid="3045"><c></c></p>
<p style="Normal" xid="3046" props="text-align:left; dom-dir:ltr">        // Checksum</p>
<p style="Normal" xid="3047" props="text-align:left; dom-dir:ltr">        uint256 hash = Hash(vRecv.begin(), vRecv.begin() + nMessageSize);</p>
<p style="Normal" xid="3048" props="text-align:left; dom-dir:ltr">        unsigned int nChecksum = 0;</p>
<p style="Normal" xid="3049" props="text-align:left; dom-dir:ltr">        memcpy(&amp;nChecksum, &amp;hash, sizeof(nChecksum));</p>
<p style="Normal" xid="3050" props="text-align:left; dom-dir:ltr">        if (nChecksum != hdr.nChecksum)</p>
<p style="Normal" xid="3051">        {</p>
<p style="Normal" xid="3052" props="text-align:left; dom-dir:ltr">            printf("ProcessMessages(%s, %u bytes) : CHECKSUM ERROR nChecksum=%08x hdr.nChecksum=%08x\n",</p>
<p style="Normal" xid="3053" props="text-align:left; dom-dir:ltr">               strCommand.c_str(), nMessageSize, nChecksum, hdr.nChecksum);</p>
<p style="Normal" xid="3054" props="text-align:left; dom-dir:ltr">            continue;</p>
<p style="Normal" xid="3055">        }</p>
<p style="Normal" xid="3056"><c></c></p>
<p style="Normal" xid="3057" props="text-align:left; dom-dir:ltr">        // Copy message to its own buffer</p>
<p style="Normal" xid="3058" props="text-align:left; dom-dir:ltr">        CDataStream vMsg(vRecv.begin(), vRecv.begin() + nMessageSize, vRecv.nType, vRecv.nVersion);</p>
<p style="Normal" xid="3059" props="text-align:left; dom-dir:ltr">        vRecv.ignore(nMessageSize);</p>
<p style="Normal" xid="3060"><c></c></p>
<p style="Normal" xid="3061" props="text-align:left; dom-dir:ltr">        // Process message</p>
<p style="Normal" xid="3062" props="text-align:left; dom-dir:ltr">        bool fRet = false;</p>
<p style="Normal" xid="3063" props="text-align:left; dom-dir:ltr">        try</p>
<p style="Normal" xid="3064">        {</p>
<p style="Normal" xid="3065">            {</p>
<p style="Normal" xid="3066" props="text-align:left; dom-dir:ltr">                LOCK(cs_main);</p>
<p style="Normal" xid="3067" props="text-align:left; dom-dir:ltr">                fRet = ProcessMessage(pfrom, strCommand, vMsg);</p>
<p style="Normal" xid="3068">            }</p>
<p style="Normal" xid="3069" props="text-align:left; dom-dir:ltr">            if (fShutdown)</p>
<p style="Normal" xid="3070" props="text-align:left; dom-dir:ltr">                return true;</p>
<p style="Normal" xid="3071">        }</p>
<p style="Normal" xid="3072" props="text-align:left; dom-dir:ltr">        catch (std::ios_base::failure&amp; e)</p>
<p style="Normal" xid="3073">        {</p>
<p style="Normal" xid="3074" props="text-align:left; dom-dir:ltr">            if (strstr(e.what(), "end of data"))</p>
<p style="Normal" xid="3075">            {</p>
<p style="Normal" xid="3076" props="text-align:left; dom-dir:ltr">                // Allow exceptions from underlength message on vRecv</p>
<p style="Normal" xid="3077" props="text-align:left; dom-dir:ltr">                printf("ProcessMessages(%s, %u bytes) : Exception '%s' caught, normally caused by a message being shorter than its stated length\n", strCommand.c_str(), nMessageSize, e.what());</p>
<p style="Normal" xid="3078">            }</p>
<p style="Normal" xid="3079" props="text-align:left; dom-dir:ltr">            else if (strstr(e.what(), "size too large"))</p>
<p style="Normal" xid="3080">            {</p>
<p style="Normal" xid="3081" props="text-align:left; dom-dir:ltr">                // Allow exceptions from overlong size</p>
<p style="Normal" xid="3082" props="text-align:left; dom-dir:ltr">                printf("ProcessMessages(%s, %u bytes) : Exception '%s' caught\n", strCommand.c_str(), nMessageSize, e.what());</p>
<p style="Normal" xid="3083">            }</p>
<p style="Normal" xid="3084" props="text-align:left; dom-dir:ltr">            else</p>
<p style="Normal" xid="3085">            {</p>
<p style="Normal" xid="3086" props="text-align:left; dom-dir:ltr">                PrintExceptionContinue(&amp;e, "ProcessMessages()");</p>
<p style="Normal" xid="3087">            }</p>
<p style="Normal" xid="3088">        }</p>
<p style="Normal" xid="3089" props="text-align:left; dom-dir:ltr">        catch (std::exception&amp; e) {</p>
<p style="Normal" xid="3090" props="text-align:left; dom-dir:ltr">            PrintExceptionContinue(&amp;e, "ProcessMessages()");</p>
<p style="Normal" xid="3091" props="text-align:left; dom-dir:ltr">        } catch (...) {</p>
<p style="Normal" xid="3092" props="text-align:left; dom-dir:ltr">            PrintExceptionContinue(NULL, "ProcessMessages()");</p>
<p style="Normal" xid="3093">        }</p>
<p style="Normal" xid="3094"><c></c></p>
<p style="Normal" xid="3095" props="text-align:left; dom-dir:ltr">        if (!fRet)</p>
<p style="Normal" xid="3096" props="text-align:left; dom-dir:ltr">            printf("ProcessMessage(%s, %u bytes) FAILED\n", strCommand.c_str(), nMessageSize);</p>
<p style="Normal" xid="3097">    }</p>
<p style="Normal" xid="3098"><c></c></p>
<p style="Normal" xid="3099" props="text-align:left; dom-dir:ltr">    vRecv.Compact();</p>
<p style="Normal" xid="3100" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="3101">}</p>
<p style="Normal" xid="3102"><c></c></p>
<p style="Normal" xid="3103"><c></c></p>
<p style="Normal" xid="3104" props="text-align:left; dom-dir:ltr">bool SendMessages(CNode* pto, bool fSendTrickle)</p>
<p style="Normal" xid="3105">{</p>
<p style="Normal" xid="3106" props="text-align:left; dom-dir:ltr">    TRY_LOCK(cs_main, lockMain);</p>
<p style="Normal" xid="3107" props="text-align:left; dom-dir:ltr">    if (lockMain) {</p>
<p style="Normal" xid="3108" props="text-align:left; dom-dir:ltr">        // Don't send anything until we get their version message</p>
<p style="Normal" xid="3109" props="text-align:left; dom-dir:ltr">        if (pto-&gt;nVersion == 0)</p>
<p style="Normal" xid="3110" props="text-align:left; dom-dir:ltr">            return true;</p>
<p style="Normal" xid="3111"><c></c></p>
<p style="Normal" xid="3112" props="text-align:left; dom-dir:ltr">        // Keep-alive ping. We send a nonce of zero because we don't use it anywhere</p>
<p style="Normal" xid="3113" props="text-align:left; dom-dir:ltr">        // right now.</p>
<p style="Normal" xid="3114" props="text-align:left; dom-dir:ltr">        if (pto-&gt;nLastSend &amp;&amp; GetTime() - pto-&gt;nLastSend &gt; 30 * 60 &amp;&amp; pto-&gt;vSend.empty()) {</p>
<p style="Normal" xid="3115" props="text-align:left; dom-dir:ltr">            uint64 nonce = 0;</p>
<p style="Normal" xid="3116" props="text-align:left; dom-dir:ltr">            if (pto-&gt;nVersion &gt; BIP0031_VERSION)</p>
<p style="Normal" xid="3117" props="text-align:left; dom-dir:ltr">                pto-&gt;PushMessage("ping", nonce);</p>
<p style="Normal" xid="3118" props="text-align:left; dom-dir:ltr">            else</p>
<p style="Normal" xid="3119" props="text-align:left; dom-dir:ltr">                pto-&gt;PushMessage("ping");</p>
<p style="Normal" xid="3120">        }</p>
<p style="Normal" xid="3121"><c></c></p>
<p style="Normal" xid="3122" props="text-align:left; dom-dir:ltr">        // Resend wallet transactions that haven't gotten in a block yet</p>
<p style="Normal" xid="3123" props="text-align:left; dom-dir:ltr">        ResendWalletTransactions();</p>
<p style="Normal" xid="3124"><c></c></p>
<p style="Normal" xid="3125" props="text-align:left; dom-dir:ltr">        // Address refresh broadcast</p>
<p style="Normal" xid="3126" props="text-align:left; dom-dir:ltr">        static int64 nLastRebroadcast;</p>
<p style="Normal" xid="3127" props="text-align:left; dom-dir:ltr">        if (!IsInitialBlockDownload() &amp;&amp; (GetTime() - nLastRebroadcast &gt; 24 * 60 * 60))</p>
<p style="Normal" xid="3128">        {</p>
<p style="Normal" xid="3129">            {</p>
<p style="Normal" xid="3130" props="text-align:left; dom-dir:ltr">                LOCK(cs_vNodes);</p>
<p style="Normal" xid="3131" props="text-align:left; dom-dir:ltr">                BOOST_FOREACH(CNode* pnode, vNodes)</p>
<p style="Normal" xid="3132">                {</p>
<p style="Normal" xid="3133" props="text-align:left; dom-dir:ltr">                    // Periodically clear setAddrKnown to allow refresh broadcasts</p>
<p style="Normal" xid="3134" props="text-align:left; dom-dir:ltr">                    if (nLastRebroadcast)</p>
<p style="Normal" xid="3135" props="text-align:left; dom-dir:ltr">                        pnode-&gt;setAddrKnown.clear();</p>
<p style="Normal" xid="3136"><c></c></p>
<p style="Normal" xid="3137" props="text-align:left; dom-dir:ltr">                    // Rebroadcast our address</p>
<p style="Normal" xid="3138" props="text-align:left; dom-dir:ltr">                    if (!fNoListen)</p>
<p style="Normal" xid="3139">                    {</p>
<p style="Normal" xid="3140" props="text-align:left; dom-dir:ltr">                        CAddress addr = GetLocalAddress(&amp;pnode-&gt;addr);</p>
<p style="Normal" xid="3141" props="text-align:left; dom-dir:ltr">                        if (addr.IsRoutable())</p>
<p style="Normal" xid="3142" props="text-align:left; dom-dir:ltr">                            pnode-&gt;PushAddress(addr);</p>
<p style="Normal" xid="3143">                    }</p>
<p style="Normal" xid="3144">                }</p>
<p style="Normal" xid="3145">            }</p>
<p style="Normal" xid="3146" props="text-align:left; dom-dir:ltr">            nLastRebroadcast = GetTime();</p>
<p style="Normal" xid="3147">        }</p>
<p style="Normal" xid="3148"><c></c></p>
<p style="Normal" xid="3149">        //</p>
<p style="Normal" xid="3150" props="text-align:left; dom-dir:ltr">        // Message: addr</p>
<p style="Normal" xid="3151">        //</p>
<p style="Normal" xid="3152" props="text-align:left; dom-dir:ltr">        if (fSendTrickle)</p>
<p style="Normal" xid="3153">        {</p>
<p style="Normal" xid="3154" props="text-align:left; dom-dir:ltr">            vector&lt;CAddress&gt; vAddr;</p>
<p style="Normal" xid="3155" props="text-align:left; dom-dir:ltr">            vAddr.reserve(pto-&gt;vAddrToSend.size());</p>
<p style="Normal" xid="3156" props="text-align:left; dom-dir:ltr">            BOOST_FOREACH(const CAddress&amp; addr, pto-&gt;vAddrToSend)</p>
<p style="Normal" xid="3157">            {</p>
<p style="Normal" xid="3158" props="text-align:left; dom-dir:ltr">                // returns true if wasn't already contained in the set</p>
<p style="Normal" xid="3159" props="text-align:left; dom-dir:ltr">                if (pto-&gt;setAddrKnown.insert(addr).second)</p>
<p style="Normal" xid="3160">                {</p>
<p style="Normal" xid="3161" props="text-align:left; dom-dir:ltr">                    vAddr.push_back(addr);</p>
<p style="Normal" xid="3162" props="text-align:left; dom-dir:ltr">                    // receiver rejects addr messages larger than 1000</p>
<p style="Normal" xid="3163" props="text-align:left; dom-dir:ltr">                    if (vAddr.size() &gt;= 1000)</p>
<p style="Normal" xid="3164">                    {</p>
<p style="Normal" xid="3165" props="text-align:left; dom-dir:ltr">                        pto-&gt;PushMessage("addr", vAddr);</p>
<p style="Normal" xid="3166" props="text-align:left; dom-dir:ltr">                        vAddr.clear();</p>
<p style="Normal" xid="3167">                    }</p>
<p style="Normal" xid="3168">                }</p>
<p style="Normal" xid="3169">            }</p>
<p style="Normal" xid="3170" props="text-align:left; dom-dir:ltr">            pto-&gt;vAddrToSend.clear();</p>
<p style="Normal" xid="3171" props="text-align:left; dom-dir:ltr">            if (!vAddr.empty())</p>
<p style="Normal" xid="3172" props="text-align:left; dom-dir:ltr">                pto-&gt;PushMessage("addr", vAddr);</p>
<p style="Normal" xid="3173">        }</p>
<p style="Normal" xid="3174"><c></c></p>
<p style="Normal" xid="3175"><c></c></p>
<p style="Normal" xid="3176">        //</p>
<p style="Normal" xid="3177" props="text-align:left; dom-dir:ltr">        // Message: inventory</p>
<p style="Normal" xid="3178">        //</p>
<p style="Normal" xid="3179" props="text-align:left; dom-dir:ltr">        vector&lt;CInv&gt; vInv;</p>
<p style="Normal" xid="3180" props="text-align:left; dom-dir:ltr">        vector&lt;CInv&gt; vInvWait;</p>
<p style="Normal" xid="3181">        {</p>
<p style="Normal" xid="3182" props="text-align:left; dom-dir:ltr">            LOCK(pto-&gt;cs_inventory);</p>
<p style="Normal" xid="3183" props="text-align:left; dom-dir:ltr">            vInv.reserve(pto-&gt;vInventoryToSend.size());</p>
<p style="Normal" xid="3184" props="text-align:left; dom-dir:ltr">            vInvWait.reserve(pto-&gt;vInventoryToSend.size());</p>
<p style="Normal" xid="3185" props="text-align:left; dom-dir:ltr">            BOOST_FOREACH(const CInv&amp; inv, pto-&gt;vInventoryToSend)</p>
<p style="Normal" xid="3186">            {</p>
<p style="Normal" xid="3187" props="text-align:left; dom-dir:ltr">                if (pto-&gt;setInventoryKnown.count(inv))</p>
<p style="Normal" xid="3188" props="text-align:left; dom-dir:ltr">                    continue;</p>
<p style="Normal" xid="3189"><c></c></p>
<p style="Normal" xid="3190" props="text-align:left; dom-dir:ltr">                // trickle out tx inv to protect privacy</p>
<p style="Normal" xid="3191" props="text-align:left; dom-dir:ltr">                if (inv.type == MSG_TX &amp;&amp; !fSendTrickle)</p>
<p style="Normal" xid="3192">                {</p>
<p style="Normal" xid="3193" props="text-align:left; dom-dir:ltr">                    // 1/4 of tx invs blast to all immediately</p>
<p style="Normal" xid="3194" props="text-align:left; dom-dir:ltr">                    static uint256 hashSalt;</p>
<p style="Normal" xid="3195" props="text-align:left; dom-dir:ltr">                    if (hashSalt == 0)</p>
<p style="Normal" xid="3196" props="text-align:left; dom-dir:ltr">                        hashSalt = GetRandHash();</p>
<p style="Normal" xid="3197" props="text-align:left; dom-dir:ltr">                    uint256 hashRand = inv.hash ^ hashSalt;</p>
<p style="Normal" xid="3198" props="text-align:left; dom-dir:ltr">                    hashRand = Hash(BEGIN(hashRand), END(hashRand));</p>
<p style="Normal" xid="3199" props="text-align:left; dom-dir:ltr">                    bool fTrickleWait = ((hashRand &amp; 3) != 0);</p>
<p style="Normal" xid="3200"><c></c></p>
<p style="Normal" xid="3201" props="text-align:left; dom-dir:ltr">                    // always trickle our own transactions</p>
<p style="Normal" xid="3202" props="text-align:left; dom-dir:ltr">                    if (!fTrickleWait)</p>
<p style="Normal" xid="3203">                    {</p>
<p style="Normal" xid="3204" props="text-align:left; dom-dir:ltr">                        CWalletTx wtx;</p>
<p style="Normal" xid="3205" props="text-align:left; dom-dir:ltr">                        if (GetTransaction(inv.hash, wtx))</p>
<p style="Normal" xid="3206" props="text-align:left; dom-dir:ltr">                            if (wtx.fFromMe)</p>
<p style="Normal" xid="3207" props="text-align:left; dom-dir:ltr">                                fTrickleWait = true;</p>
<p style="Normal" xid="3208">                    }</p>
<p style="Normal" xid="3209"><c></c></p>
<p style="Normal" xid="3210" props="text-align:left; dom-dir:ltr">                    if (fTrickleWait)</p>
<p style="Normal" xid="3211">                    {</p>
<p style="Normal" xid="3212" props="text-align:left; dom-dir:ltr">                        vInvWait.push_back(inv);</p>
<p style="Normal" xid="3213" props="text-align:left; dom-dir:ltr">                        continue;</p>
<p style="Normal" xid="3214">                    }</p>
<p style="Normal" xid="3215">                }</p>
<p style="Normal" xid="3216"><c></c></p>
<p style="Normal" xid="3217" props="text-align:left; dom-dir:ltr">                // returns true if wasn't already contained in the set</p>
<p style="Normal" xid="3218" props="text-align:left; dom-dir:ltr">                if (pto-&gt;setInventoryKnown.insert(inv).second)</p>
<p style="Normal" xid="3219">                {</p>
<p style="Normal" xid="3220" props="text-align:left; dom-dir:ltr">                    vInv.push_back(inv);</p>
<p style="Normal" xid="3221" props="text-align:left; dom-dir:ltr">                    if (vInv.size() &gt;= 1000)</p>
<p style="Normal" xid="3222">                    {</p>
<p style="Normal" xid="3223" props="text-align:left; dom-dir:ltr">                        pto-&gt;PushMessage("inv", vInv);</p>
<p style="Normal" xid="3224" props="text-align:left; dom-dir:ltr">                        vInv.clear();</p>
<p style="Normal" xid="3225">                    }</p>
<p style="Normal" xid="3226">                }</p>
<p style="Normal" xid="3227">            }</p>
<p style="Normal" xid="3228" props="text-align:left; dom-dir:ltr">            pto-&gt;vInventoryToSend = vInvWait;</p>
<p style="Normal" xid="3229">        }</p>
<p style="Normal" xid="3230" props="text-align:left; dom-dir:ltr">        if (!vInv.empty())</p>
<p style="Normal" xid="3231" props="text-align:left; dom-dir:ltr">            pto-&gt;PushMessage("inv", vInv);</p>
<p style="Normal" xid="3232"><c></c></p>
<p style="Normal" xid="3233"><c></c></p>
<p style="Normal" xid="3234">        //</p>
<p style="Normal" xid="3235" props="text-align:left; dom-dir:ltr">        // Message: getdata</p>
<p style="Normal" xid="3236">        //</p>
<p style="Normal" xid="3237" props="text-align:left; dom-dir:ltr">        vector&lt;CInv&gt; vGetData;</p>
<p style="Normal" xid="3238" props="text-align:left; dom-dir:ltr">        int64 nNow = GetTime() * 1000000;</p>
<p style="Normal" xid="3239" props="text-align:left; dom-dir:ltr">        CTxDB txdb("r");</p>
<p style="Normal" xid="3240" props="text-align:left; dom-dir:ltr">        while (!pto-&gt;mapAskFor.empty() &amp;&amp; (*pto-&gt;mapAskFor.begin()).first &lt;= nNow)</p>
<p style="Normal" xid="3241">        {</p>
<p style="Normal" xid="3242" props="text-align:left; dom-dir:ltr">            const CInv&amp; inv = (*pto-&gt;mapAskFor.begin()).second;</p>
<p style="Normal" xid="3243" props="text-align:left; dom-dir:ltr">            if (!AlreadyHave(txdb, inv))</p>
<p style="Normal" xid="3244">            {</p>
<p style="Normal" xid="3245" props="text-align:left; dom-dir:ltr">                if (fDebugNet)</p>
<p style="Normal" xid="3246" props="text-align:left; dom-dir:ltr">                    printf("sending getdata: %s\n", inv.ToString().c_str());</p>
<p style="Normal" xid="3247" props="text-align:left; dom-dir:ltr">                vGetData.push_back(inv);</p>
<p style="Normal" xid="3248" props="text-align:left; dom-dir:ltr">                if (vGetData.size() &gt;= 1000)</p>
<p style="Normal" xid="3249">                {</p>
<p style="Normal" xid="3250" props="text-align:left; dom-dir:ltr">                    pto-&gt;PushMessage("getdata", vGetData);</p>
<p style="Normal" xid="3251" props="text-align:left; dom-dir:ltr">                    vGetData.clear();</p>
<p style="Normal" xid="3252">                }</p>
<p style="Normal" xid="3253" props="text-align:left; dom-dir:ltr">                mapAlreadyAskedFor[inv] = nNow;</p>
<p style="Normal" xid="3254">            }</p>
<p style="Normal" xid="3255" props="text-align:left; dom-dir:ltr">            pto-&gt;mapAskFor.erase(pto-&gt;mapAskFor.begin());</p>
<p style="Normal" xid="3256">        }</p>
<p style="Normal" xid="3257" props="text-align:left; dom-dir:ltr">        if (!vGetData.empty())</p>
<p style="Normal" xid="3258" props="text-align:left; dom-dir:ltr">            pto-&gt;PushMessage("getdata", vGetData);</p>
<p style="Normal" xid="3259"><c></c></p>
<p style="Normal" xid="3260">    }</p>
<p style="Normal" xid="3261" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="3262">}</p>
<p style="Normal" xid="3263"><c></c></p>
<p style="Normal" xid="3264"><c></c></p>
<p style="Normal" xid="3265"><c></c></p>
<p style="Normal" xid="3266"><c></c></p>
<p style="Normal" xid="3267"><c></c></p>
<p style="Normal" xid="3268"><c></c></p>
<p style="Normal" xid="3269"><c></c></p>
<p style="Normal" xid="3270"><c></c></p>
<p style="Normal" xid="3271"><c></c></p>
<p style="Normal" xid="3272"><c></c></p>
<p style="Normal" xid="3273"><c></c></p>
<p style="Normal" xid="3274"><c></c></p>
<p style="Normal" xid="3275"><c></c></p>
<p style="Normal" xid="3276"><c></c></p>
<p style="Normal" xid="3277">//////////////////////////////////////////////////////////////////////////////</p>
<p style="Normal" xid="3278">//</p>
<p style="Normal" xid="3279" props="text-align:left; dom-dir:ltr">// BitcoinMiner</p>
<p style="Normal" xid="3280">//</p>
<p style="Normal" xid="3281"><c></c></p>
<p style="Normal" xid="3282" props="text-align:left; dom-dir:ltr">int static FormatHashBlocks(void* pbuffer, unsigned int len)</p>
<p style="Normal" xid="3283">{</p>
<p style="Normal" xid="3284" props="text-align:left; dom-dir:ltr">    unsigned char* pdata = (unsigned char*)pbuffer;</p>
<p style="Normal" xid="3285" props="text-align:left; dom-dir:ltr">    unsigned int blocks = 1 + ((len + 8) / 64);</p>
<p style="Normal" xid="3286" props="text-align:left; dom-dir:ltr">    unsigned char* pend = pdata + 64 * blocks;</p>
<p style="Normal" xid="3287" props="text-align:left; dom-dir:ltr">    memset(pdata + len, 0, 64 * blocks - len);</p>
<p style="Normal" xid="3288" props="text-align:left; dom-dir:ltr">    pdata[len] = 0x80;</p>
<p style="Normal" xid="3289" props="text-align:left; dom-dir:ltr">    unsigned int bits = len * 8;</p>
<p style="Normal" xid="3290" props="text-align:left; dom-dir:ltr">    pend[-1] = (bits &gt;&gt; 0) &amp; 0xff;</p>
<p style="Normal" xid="3291" props="text-align:left; dom-dir:ltr">    pend[-2] = (bits &gt;&gt; 8) &amp; 0xff;</p>
<p style="Normal" xid="3292" props="text-align:left; dom-dir:ltr">    pend[-3] = (bits &gt;&gt; 16) &amp; 0xff;</p>
<p style="Normal" xid="3293" props="text-align:left; dom-dir:ltr">    pend[-4] = (bits &gt;&gt; 24) &amp; 0xff;</p>
<p style="Normal" xid="3294" props="text-align:left; dom-dir:ltr">    return blocks;</p>
<p style="Normal" xid="3295">}</p>
<p style="Normal" xid="3296"><c></c></p>
<p style="Normal" xid="3297" props="text-align:left; dom-dir:ltr">static const unsigned int pSHA256InitState[8] =</p>
<p style="Normal" xid="3298" props="text-align:left; dom-dir:ltr">{0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};</p>
<p style="Normal" xid="3299"><c></c></p>
<p style="Normal" xid="3300" props="text-align:left; dom-dir:ltr">void SHA256Transform(void* pstate, void* pinput, const void* pinit)</p>
<p style="Normal" xid="3301">{</p>
<p style="Normal" xid="3302" props="text-align:left; dom-dir:ltr">    SHA256_CTX ctx;</p>
<p style="Normal" xid="3303" props="text-align:left; dom-dir:ltr">    unsigned char data[64];</p>
<p style="Normal" xid="3304"><c></c></p>
<p style="Normal" xid="3305" props="text-align:left; dom-dir:ltr">    SHA256_Init(&amp;ctx);</p>
<p style="Normal" xid="3306"><c></c></p>
<p style="Normal" xid="3307" props="text-align:left; dom-dir:ltr">    for (int i = 0; i &lt; 16; i++)</p>
<p style="Normal" xid="3308" props="text-align:left; dom-dir:ltr">        ((uint32_t*)data)[i] = ByteReverse(((uint32_t*)pinput)[i]);</p>
<p style="Normal" xid="3309"><c></c></p>
<p style="Normal" xid="3310" props="text-align:left; dom-dir:ltr">    for (int i = 0; i &lt; 8; i++)</p>
<p style="Normal" xid="3311" props="text-align:left; dom-dir:ltr">        ctx.h[i] = ((uint32_t*)pinit)[i];</p>
<p style="Normal" xid="3312"><c></c></p>
<p style="Normal" xid="3313" props="text-align:left; dom-dir:ltr">    SHA256_Update(&amp;ctx, data, sizeof(data));</p>
<p style="Normal" xid="3314" props="text-align:left; dom-dir:ltr">    for (int i = 0; i &lt; 8; i++)</p>
<p style="Normal" xid="3315" props="text-align:left; dom-dir:ltr">        ((uint32_t*)pstate)[i] = ctx.h[i];</p>
<p style="Normal" xid="3316">}</p>
<p style="Normal" xid="3317"><c></c></p>
<p style="Normal" xid="3318">//</p>
<p style="Normal" xid="3319" props="text-align:left; dom-dir:ltr">// ScanHash scans nonces looking for a hash with at least some zero bits.</p>
<p style="Normal" xid="3320" props="text-align:left; dom-dir:ltr">// It operates on big endian data.  Caller does the byte reversing.</p>
<p style="Normal" xid="3321" props="text-align:left; dom-dir:ltr">// All input buffers are 16-byte aligned.  nNonce is usually preserved</p>
<p style="Normal" xid="3322" props="text-align:left; dom-dir:ltr">// between calls, but periodically or if nNonce is 0xffff0000 or above,</p>
<p style="Normal" xid="3323" props="text-align:left; dom-dir:ltr">// the block is rebuilt and nNonce starts over at zero.</p>
<p style="Normal" xid="3324">//</p>
<p style="Normal" xid="3325" props="text-align:left; dom-dir:ltr">unsigned int static ScanHash_CryptoPP(char* pmidstate, char* pdata, char* phash1, char* phash, unsigned int&amp; nHashesDone)</p>
<p style="Normal" xid="3326">{</p>
<p style="Normal" xid="3327" props="text-align:left; dom-dir:ltr">    unsigned int&amp; nNonce = *(unsigned int*)(pdata + 12);</p>
<p style="Normal" xid="3328" props="text-align:left; dom-dir:ltr">    for (;;)</p>
<p style="Normal" xid="3329">    {</p>
<p style="Normal" xid="3330" props="text-align:left; dom-dir:ltr">        // Crypto++ SHA-256</p>
<p style="Normal" xid="3331" props="text-align:left; dom-dir:ltr">        // Hash pdata using pmidstate as the starting state into</p>
<p style="Normal" xid="3332" props="text-align:left; dom-dir:ltr">        // preformatted buffer phash1, then hash phash1 into phash</p>
<p style="Normal" xid="3333" props="text-align:left; dom-dir:ltr">        nNonce++;</p>
<p style="Normal" xid="3334" props="text-align:left; dom-dir:ltr">        SHA256Transform(phash1, pdata, pmidstate);</p>
<p style="Normal" xid="3335" props="text-align:left; dom-dir:ltr">        SHA256Transform(phash, phash1, pSHA256InitState);</p>
<p style="Normal" xid="3336"><c></c></p>
<p style="Normal" xid="3337" props="text-align:left; dom-dir:ltr">        // Return the nonce if the hash has at least some zero bits,</p>
<p style="Normal" xid="3338" props="text-align:left; dom-dir:ltr">        // caller will check if it has enough to reach the target</p>
<p style="Normal" xid="3339" props="text-align:left; dom-dir:ltr">        if (((unsigned short*)phash)[14] == 0)</p>
<p style="Normal" xid="3340" props="text-align:left; dom-dir:ltr">            return nNonce;</p>
<p style="Normal" xid="3341"><c></c></p>
<p style="Normal" xid="3342" props="text-align:left; dom-dir:ltr">        // If nothing found after trying for a while, return -1</p>
<p style="Normal" xid="3343" props="text-align:left; dom-dir:ltr">        if ((nNonce &amp; 0xffff) == 0)</p>
<p style="Normal" xid="3344">        {</p>
<p style="Normal" xid="3345" props="text-align:left; dom-dir:ltr">            nHashesDone = 0xffff+1;</p>
<p style="Normal" xid="3346" props="text-align:left; dom-dir:ltr">            return (unsigned int) -1;</p>
<p style="Normal" xid="3347">        }</p>
<p style="Normal" xid="3348">    }</p>
<p style="Normal" xid="3349">}</p>
<p style="Normal" xid="3350"><c></c></p>
<p style="Normal" xid="3351" props="text-align:left; dom-dir:ltr">// Some explaining would be appreciated</p>
<p style="Normal" xid="3352" props="text-align:left; dom-dir:ltr">class COrphan</p>
<p style="Normal" xid="3353">{</p>
<p style="Normal" xid="3354" props="text-align:left; dom-dir:ltr">public:</p>
<p style="Normal" xid="3355" props="text-align:left; dom-dir:ltr">    CTransaction* ptx;</p>
<p style="Normal" xid="3356" props="text-align:left; dom-dir:ltr">    set&lt;uint256&gt; setDependsOn;</p>
<p style="Normal" xid="3357" props="text-align:left; dom-dir:ltr">    double dPriority;</p>
<p style="Normal" xid="3358"><c></c></p>
<p style="Normal" xid="3359" props="text-align:left; dom-dir:ltr">    COrphan(CTransaction* ptxIn)</p>
<p style="Normal" xid="3360">    {</p>
<p style="Normal" xid="3361" props="text-align:left; dom-dir:ltr">        ptx = ptxIn;</p>
<p style="Normal" xid="3362" props="text-align:left; dom-dir:ltr">        dPriority = 0;</p>
<p style="Normal" xid="3363">    }</p>
<p style="Normal" xid="3364"><c></c></p>
<p style="Normal" xid="3365" props="text-align:left; dom-dir:ltr">    void print() const</p>
<p style="Normal" xid="3366">    {</p>
<p style="Normal" xid="3367" props="text-align:left; dom-dir:ltr">        printf("COrphan(hash=%s, dPriority=%.1f)\n", ptx-&gt;GetHash().ToString().substr(0,10).c_str(), dPriority);</p>
<p style="Normal" xid="3368" props="text-align:left; dom-dir:ltr">        BOOST_FOREACH(uint256 hash, setDependsOn)</p>
<p style="Normal" xid="3369" props="text-align:left; dom-dir:ltr">            printf("   setDependsOn %s\n", hash.ToString().substr(0,10).c_str());</p>
<p style="Normal" xid="3370">    }</p>
<p style="Normal" xid="3371">};</p>
<p style="Normal" xid="3372"><c></c></p>
<p style="Normal" xid="3373"><c></c></p>
<p style="Normal" xid="3374" props="text-align:left; dom-dir:ltr">uint64 nLastBlockTx = 0;</p>
<p style="Normal" xid="3375" props="text-align:left; dom-dir:ltr">uint64 nLastBlockSize = 0;</p>
<p style="Normal" xid="3376"><c></c></p>
<p style="Normal" xid="3377" props="text-align:left; dom-dir:ltr">CBlock* CreateNewBlock(CReserveKey&amp; reservekey)</p>
<p style="Normal" xid="3378">{</p>
<p style="Normal" xid="3379" props="text-align:left; dom-dir:ltr">    CBlockIndex* pindexPrev = pindexBest;</p>
<p style="Normal" xid="3380"><c></c></p>
<p style="Normal" xid="3381" props="text-align:left; dom-dir:ltr">    // Create new block</p>
<p style="Normal" xid="3382" props="text-align:left; dom-dir:ltr">    auto_ptr&lt;CBlock&gt; pblock(new CBlock());</p>
<p style="Normal" xid="3383" props="text-align:left; dom-dir:ltr">    if (!pblock.get())</p>
<p style="Normal" xid="3384" props="text-align:left; dom-dir:ltr">        return NULL;</p>
<p style="Normal" xid="3385"><c></c></p>
<p style="Normal" xid="3386" props="text-align:left; dom-dir:ltr">    // Create coinbase tx</p>
<p style="Normal" xid="3387" props="text-align:left; dom-dir:ltr">    CTransaction txNew;</p>
<p style="Normal" xid="3388" props="text-align:left; dom-dir:ltr">    txNew.vin.resize(1);</p>
<p style="Normal" xid="3389" props="text-align:left; dom-dir:ltr">    txNew.vin[0].prevout.SetNull();</p>
<p style="Normal" xid="3390" props="text-align:left; dom-dir:ltr">    txNew.vout.resize(1);</p>
<p style="Normal" xid="3391" props="text-align:left; dom-dir:ltr">    txNew.vout[0].scriptPubKey &lt;&lt; reservekey.GetReservedKey() &lt;&lt; OP_CHECKSIG;</p>
<p style="Normal" xid="3392"><c></c></p>
<p style="Normal" xid="3393" props="text-align:left; dom-dir:ltr">    // Add our coinbase tx as first transaction</p>
<p style="Normal" xid="3394" props="text-align:left; dom-dir:ltr">    pblock-&gt;vtx.push_back(txNew);</p>
<p style="Normal" xid="3395"><c></c></p>
<p style="Normal" xid="3396" props="text-align:left; dom-dir:ltr">    // Collect memory pool transactions into the block</p>
<p style="Normal" xid="3397" props="text-align:left; dom-dir:ltr">    int64 nFees = 0;</p>
<p style="Normal" xid="3398">    {</p>
<p style="Normal" xid="3399" props="text-align:left; dom-dir:ltr">        LOCK2(cs_main, mempool.cs);</p>
<p style="Normal" xid="3400" props="text-align:left; dom-dir:ltr">        CTxDB txdb("r");</p>
<p style="Normal" xid="3401"><c></c></p>
<p style="Normal" xid="3402" props="text-align:left; dom-dir:ltr">        // Priority order to process transactions</p>
<p style="Normal" xid="3403" props="text-align:left; dom-dir:ltr">        list&lt;COrphan&gt; vOrphan; // list memory doesn't move</p>
<p style="Normal" xid="3404" props="text-align:left; dom-dir:ltr">        map&lt;uint256, vector&lt;COrphan*&gt; &gt; mapDependers;</p>
<p style="Normal" xid="3405" props="text-align:left; dom-dir:ltr">        multimap&lt;double, CTransaction*&gt; mapPriority;</p>
<p style="Normal" xid="3406" props="text-align:left; dom-dir:ltr">        for (map&lt;uint256, CTransaction&gt;::iterator mi = mempool.mapTx.begin(); mi != mempool.mapTx.end(); ++mi)</p>
<p style="Normal" xid="3407">        {</p>
<p style="Normal" xid="3408" props="text-align:left; dom-dir:ltr">            CTransaction&amp; tx = (*mi).second;</p>
<p style="Normal" xid="3409" props="text-align:left; dom-dir:ltr">            if (tx.IsCoinBase() || !tx.IsFinal())</p>
<p style="Normal" xid="3410" props="text-align:left; dom-dir:ltr">                continue;</p>
<p style="Normal" xid="3411"><c></c></p>
<p style="Normal" xid="3412" props="text-align:left; dom-dir:ltr">            COrphan* porphan = NULL;</p>
<p style="Normal" xid="3413" props="text-align:left; dom-dir:ltr">            double dPriority = 0;</p>
<p style="Normal" xid="3414" props="text-align:left; dom-dir:ltr">            BOOST_FOREACH(const CTxIn&amp; txin, tx.vin)</p>
<p style="Normal" xid="3415">            {</p>
<p style="Normal" xid="3416" props="text-align:left; dom-dir:ltr">                // Read prev transaction</p>
<p style="Normal" xid="3417" props="text-align:left; dom-dir:ltr">                CTransaction txPrev;</p>
<p style="Normal" xid="3418" props="text-align:left; dom-dir:ltr">                CTxIndex txindex;</p>
<p style="Normal" xid="3419" props="text-align:left; dom-dir:ltr">                if (!txPrev.ReadFromDisk(txdb, txin.prevout, txindex))</p>
<p style="Normal" xid="3420">                {</p>
<p style="Normal" xid="3421" props="text-align:left; dom-dir:ltr">                    // Has to wait for dependencies</p>
<p style="Normal" xid="3422" props="text-align:left; dom-dir:ltr">                    if (!porphan)</p>
<p style="Normal" xid="3423">                    {</p>
<p style="Normal" xid="3424" props="text-align:left; dom-dir:ltr">                        // Use list for automatic deletion</p>
<p style="Normal" xid="3425" props="text-align:left; dom-dir:ltr">                        vOrphan.push_back(COrphan(&amp;tx));</p>
<p style="Normal" xid="3426" props="text-align:left; dom-dir:ltr">                        porphan = &amp;vOrphan.back();</p>
<p style="Normal" xid="3427">                    }</p>
<p style="Normal" xid="3428" props="text-align:left; dom-dir:ltr">                    mapDependers[txin.prevout.hash].push_back(porphan);</p>
<p style="Normal" xid="3429" props="text-align:left; dom-dir:ltr">                    porphan-&gt;setDependsOn.insert(txin.prevout.hash);</p>
<p style="Normal" xid="3430" props="text-align:left; dom-dir:ltr">                    continue;</p>
<p style="Normal" xid="3431">                }</p>
<p style="Normal" xid="3432" props="text-align:left; dom-dir:ltr">                int64 nValueIn = txPrev.vout[txin.prevout.n].nValue;</p>
<p style="Normal" xid="3433"><c></c></p>
<p style="Normal" xid="3434" props="text-align:left; dom-dir:ltr">                // Read block header</p>
<p style="Normal" xid="3435" props="text-align:left; dom-dir:ltr">                int nConf = txindex.GetDepthInMainChain();</p>
<p style="Normal" xid="3436"><c></c></p>
<p style="Normal" xid="3437" props="text-align:left; dom-dir:ltr">                dPriority += (double)nValueIn * nConf;</p>
<p style="Normal" xid="3438"><c></c></p>
<p style="Normal" xid="3439" props="text-align:left; dom-dir:ltr">                if (fDebug &amp;&amp; GetBoolArg("-printpriority"))</p>
<p style="Normal" xid="3440" props="text-align:left; dom-dir:ltr">                    printf("priority     nValueIn=%-12"PRI64d" nConf=%-5d dPriority=%-20.1f\n", nValueIn, nConf, dPriority);</p>
<p style="Normal" xid="3441">            }</p>
<p style="Normal" xid="3442"><c></c></p>
<p style="Normal" xid="3443" props="text-align:left; dom-dir:ltr">            // Priority is sum(valuein * age) / txsize</p>
<p style="Normal" xid="3444" props="text-align:left; dom-dir:ltr">            dPriority /= ::GetSerializeSize(tx, SER_NETWORK, PROTOCOL_VERSION);</p>
<p style="Normal" xid="3445"><c></c></p>
<p style="Normal" xid="3446" props="text-align:left; dom-dir:ltr">            if (porphan)</p>
<p style="Normal" xid="3447" props="text-align:left; dom-dir:ltr">                porphan-&gt;dPriority = dPriority;</p>
<p style="Normal" xid="3448" props="text-align:left; dom-dir:ltr">            else</p>
<p style="Normal" xid="3449" props="text-align:left; dom-dir:ltr">                mapPriority.insert(make_pair(-dPriority, &amp;(*mi).second));</p>
<p style="Normal" xid="3450"><c></c></p>
<p style="Normal" xid="3451" props="text-align:left; dom-dir:ltr">            if (fDebug &amp;&amp; GetBoolArg("-printpriority"))</p>
<p style="Normal" xid="3452">            {</p>
<p style="Normal" xid="3453" props="text-align:left; dom-dir:ltr">                printf("priority %-20.1f %s\n%s", dPriority, tx.GetHash().ToString().substr(0,10).c_str(), tx.ToString().c_str());</p>
<p style="Normal" xid="3454" props="text-align:left; dom-dir:ltr">                if (porphan)</p>
<p style="Normal" xid="3455" props="text-align:left; dom-dir:ltr">                    porphan-&gt;print();</p>
<p style="Normal" xid="3456" props="text-align:left; dom-dir:ltr">                printf("\n");</p>
<p style="Normal" xid="3457">            }</p>
<p style="Normal" xid="3458">        }</p>
<p style="Normal" xid="3459"><c></c></p>
<p style="Normal" xid="3460" props="text-align:left; dom-dir:ltr">        // Collect transactions into block</p>
<p style="Normal" xid="3461" props="text-align:left; dom-dir:ltr">        map&lt;uint256, CTxIndex&gt; mapTestPool;</p>
<p style="Normal" xid="3462" props="text-align:left; dom-dir:ltr">        uint64 nBlockSize = 1000;</p>
<p style="Normal" xid="3463" props="text-align:left; dom-dir:ltr">        uint64 nBlockTx = 0;</p>
<p style="Normal" xid="3464" props="text-align:left; dom-dir:ltr">        int nBlockSigOps = 100;</p>
<p style="Normal" xid="3465" props="text-align:left; dom-dir:ltr">        while (!mapPriority.empty())</p>
<p style="Normal" xid="3466">        {</p>
<p style="Normal" xid="3467" props="text-align:left; dom-dir:ltr">            // Take highest priority transaction off priority queue</p>
<p style="Normal" xid="3468" props="text-align:left; dom-dir:ltr">            double dPriority = -(*mapPriority.begin()).first;</p>
<p style="Normal" xid="3469" props="text-align:left; dom-dir:ltr">            CTransaction&amp; tx = *(*mapPriority.begin()).second;</p>
<p style="Normal" xid="3470" props="text-align:left; dom-dir:ltr">            mapPriority.erase(mapPriority.begin());</p>
<p style="Normal" xid="3471"><c></c></p>
<p style="Normal" xid="3472" props="text-align:left; dom-dir:ltr">            // Size limits</p>
<p style="Normal" xid="3473" props="text-align:left; dom-dir:ltr">            unsigned int nTxSize = ::GetSerializeSize(tx, SER_NETWORK, PROTOCOL_VERSION);</p>
<p style="Normal" xid="3474" props="text-align:left; dom-dir:ltr">            if (nBlockSize + nTxSize &gt;= MAX_BLOCK_SIZE_GEN)</p>
<p style="Normal" xid="3475" props="text-align:left; dom-dir:ltr">                continue;</p>
<p style="Normal" xid="3476"><c></c></p>
<p style="Normal" xid="3477" props="text-align:left; dom-dir:ltr">            // Legacy limits on sigOps:</p>
<p style="Normal" xid="3478" props="text-align:left; dom-dir:ltr">            unsigned int nTxSigOps = tx.GetLegacySigOpCount();</p>
<p style="Normal" xid="3479" props="text-align:left; dom-dir:ltr">            if (nBlockSigOps + nTxSigOps &gt;= MAX_BLOCK_SIGOPS)</p>
<p style="Normal" xid="3480" props="text-align:left; dom-dir:ltr">                continue;</p>
<p style="Normal" xid="3481"><c></c></p>
<p style="Normal" xid="3482" props="text-align:left; dom-dir:ltr">            // Transaction fee required depends on block size</p>
<p style="Normal" xid="3483" props="text-align:left; dom-dir:ltr">            // Litecoind: Reduce the exempted free transactions to 500 bytes (from Bitcoin's 3000 bytes)</p>
<p style="Normal" xid="3484" props="text-align:left; dom-dir:ltr">            bool fAllowFree = (nBlockSize + nTxSize &lt; 1500 || CTransaction::AllowFree(dPriority));</p>
<p style="Normal" xid="3485" props="text-align:left; dom-dir:ltr">            int64 nMinFee = tx.GetMinFee(nBlockSize, fAllowFree, GMF_BLOCK);</p>
<p style="Normal" xid="3486"><c></c></p>
<p style="Normal" xid="3487" props="text-align:left; dom-dir:ltr">            // Connecting shouldn't fail due to dependency on other memory pool transactions</p>
<p style="Normal" xid="3488" props="text-align:left; dom-dir:ltr">            // because we're already processing them in order of dependency</p>
<p style="Normal" xid="3489" props="text-align:left; dom-dir:ltr">            map&lt;uint256, CTxIndex&gt; mapTestPoolTmp(mapTestPool);</p>
<p style="Normal" xid="3490" props="text-align:left; dom-dir:ltr">            MapPrevTx mapInputs;</p>
<p style="Normal" xid="3491" props="text-align:left; dom-dir:ltr">            bool fInvalid;</p>
<p style="Normal" xid="3492" props="text-align:left; dom-dir:ltr">            if (!tx.FetchInputs(txdb, mapTestPoolTmp, false, true, mapInputs, fInvalid))</p>
<p style="Normal" xid="3493" props="text-align:left; dom-dir:ltr">                continue;</p>
<p style="Normal" xid="3494"><c></c></p>
<p style="Normal" xid="3495" props="text-align:left; dom-dir:ltr">            int64 nTxFees = tx.GetValueIn(mapInputs)-tx.GetValueOut();</p>
<p style="Normal" xid="3496" props="text-align:left; dom-dir:ltr">            if (nTxFees &lt; nMinFee)</p>
<p style="Normal" xid="3497" props="text-align:left; dom-dir:ltr">                continue;</p>
<p style="Normal" xid="3498"><c></c></p>
<p style="Normal" xid="3499" props="text-align:left; dom-dir:ltr">            nTxSigOps += tx.GetP2SHSigOpCount(mapInputs);</p>
<p style="Normal" xid="3500" props="text-align:left; dom-dir:ltr">            if (nBlockSigOps + nTxSigOps &gt;= MAX_BLOCK_SIGOPS)</p>
<p style="Normal" xid="3501" props="text-align:left; dom-dir:ltr">                continue;</p>
<p style="Normal" xid="3502"><c></c></p>
<p style="Normal" xid="3503" props="text-align:left; dom-dir:ltr">            if (!tx.ConnectInputs(mapInputs, mapTestPoolTmp, CDiskTxPos(1,1,1), pindexPrev, false, true))</p>
<p style="Normal" xid="3504" props="text-align:left; dom-dir:ltr">                continue;</p>
<p style="Normal" xid="3505" props="text-align:left; dom-dir:ltr">            mapTestPoolTmp[tx.GetHash()] = CTxIndex(CDiskTxPos(1,1,1), tx.vout.size());</p>
<p style="Normal" xid="3506" props="text-align:left; dom-dir:ltr">            swap(mapTestPool, mapTestPoolTmp);</p>
<p style="Normal" xid="3507"><c></c></p>
<p style="Normal" xid="3508" props="text-align:left; dom-dir:ltr">            // Added</p>
<p style="Normal" xid="3509" props="text-align:left; dom-dir:ltr">            pblock-&gt;vtx.push_back(tx);</p>
<p style="Normal" xid="3510" props="text-align:left; dom-dir:ltr">            nBlockSize += nTxSize;</p>
<p style="Normal" xid="3511" props="text-align:left; dom-dir:ltr">            ++nBlockTx;</p>
<p style="Normal" xid="3512" props="text-align:left; dom-dir:ltr">            nBlockSigOps += nTxSigOps;</p>
<p style="Normal" xid="3513" props="text-align:left; dom-dir:ltr">            nFees += nTxFees;</p>
<p style="Normal" xid="3514"><c></c></p>
<p style="Normal" xid="3515" props="text-align:left; dom-dir:ltr">            // Add transactions that depend on this one to the priority queue</p>
<p style="Normal" xid="3516" props="text-align:left; dom-dir:ltr">            uint256 hash = tx.GetHash();</p>
<p style="Normal" xid="3517" props="text-align:left; dom-dir:ltr">            if (mapDependers.count(hash))</p>
<p style="Normal" xid="3518">            {</p>
<p style="Normal" xid="3519" props="text-align:left; dom-dir:ltr">                BOOST_FOREACH(COrphan* porphan, mapDependers[hash])</p>
<p style="Normal" xid="3520">                {</p>
<p style="Normal" xid="3521" props="text-align:left; dom-dir:ltr">                    if (!porphan-&gt;setDependsOn.empty())</p>
<p style="Normal" xid="3522">                    {</p>
<p style="Normal" xid="3523" props="text-align:left; dom-dir:ltr">                        porphan-&gt;setDependsOn.erase(hash);</p>
<p style="Normal" xid="3524" props="text-align:left; dom-dir:ltr">                        if (porphan-&gt;setDependsOn.empty())</p>
<p style="Normal" xid="3525" props="text-align:left; dom-dir:ltr">                            mapPriority.insert(make_pair(-porphan-&gt;dPriority, porphan-&gt;ptx));</p>
<p style="Normal" xid="3526">                    }</p>
<p style="Normal" xid="3527">                }</p>
<p style="Normal" xid="3528">            }</p>
<p style="Normal" xid="3529">        }</p>
<p style="Normal" xid="3530"><c></c></p>
<p style="Normal" xid="3531" props="text-align:left; dom-dir:ltr">        nLastBlockTx = nBlockTx;</p>
<p style="Normal" xid="3532" props="text-align:left; dom-dir:ltr">        nLastBlockSize = nBlockSize;</p>
<p style="Normal" xid="3533" props="text-align:left; dom-dir:ltr">        printf("CreateNewBlock(): total size %lu\n", nBlockSize);</p>
<p style="Normal" xid="3534"><c></c></p>
<p style="Normal" xid="3535">    }</p>
<p style="Normal" xid="3536" props="text-align:left; dom-dir:ltr">    pblock-&gt;vtx[0].vout[0].nValue = GetBlockValue(pindexPrev-&gt;nHeight+1, nFees);</p>
<p style="Normal" xid="3537"><c></c></p>
<p style="Normal" xid="3538" props="text-align:left; dom-dir:ltr">    // Fill in header</p>
<p style="Normal" xid="3539" props="text-align:left; dom-dir:ltr">    pblock-&gt;hashPrevBlock  = pindexPrev-&gt;GetBlockHash();</p>
<p style="Normal" xid="3540" props="text-align:left; dom-dir:ltr">    pblock-&gt;hashMerkleRoot = pblock-&gt;BuildMerkleTree();</p>
<p style="Normal" xid="3541" props="text-align:left; dom-dir:ltr">    pblock-&gt;UpdateTime(pindexPrev);</p>
<p style="Normal" xid="3542" props="text-align:left; dom-dir:ltr">    pblock-&gt;nBits          = GetNextWorkRequired(pindexPrev, pblock.get());</p>
<p style="Normal" xid="3543" props="text-align:left; dom-dir:ltr">    pblock-&gt;nNonce         = 0;</p>
<p style="Normal" xid="3544"><c></c></p>
<p style="Normal" xid="3545" props="text-align:left; dom-dir:ltr">    return pblock.release();</p>
<p style="Normal" xid="3546">}</p>
<p style="Normal" xid="3547"><c></c></p>
<p style="Normal" xid="3548"><c></c></p>
<p style="Normal" xid="3549" props="text-align:left; dom-dir:ltr">void IncrementExtraNonce(CBlock* pblock, CBlockIndex* pindexPrev, unsigned int&amp; nExtraNonce)</p>
<p style="Normal" xid="3550">{</p>
<p style="Normal" xid="3551" props="text-align:left; dom-dir:ltr">    // Update nExtraNonce</p>
<p style="Normal" xid="3552" props="text-align:left; dom-dir:ltr">    static uint256 hashPrevBlock;</p>
<p style="Normal" xid="3553" props="text-align:left; dom-dir:ltr">    if (hashPrevBlock != pblock-&gt;hashPrevBlock)</p>
<p style="Normal" xid="3554">    {</p>
<p style="Normal" xid="3555" props="text-align:left; dom-dir:ltr">        nExtraNonce = 0;</p>
<p style="Normal" xid="3556" props="text-align:left; dom-dir:ltr">        hashPrevBlock = pblock-&gt;hashPrevBlock;</p>
<p style="Normal" xid="3557">    }</p>
<p style="Normal" xid="3558" props="text-align:left; dom-dir:ltr">    ++nExtraNonce;</p>
<p style="Normal" xid="3559" props="text-align:left; dom-dir:ltr">    pblock-&gt;vtx[0].vin[0].scriptSig = (CScript() &lt;&lt; pblock-&gt;nTime &lt;&lt; CBigNum(nExtraNonce)) + COINBASE_FLAGS;</p>
<p style="Normal" xid="3560" props="text-align:left; dom-dir:ltr">    assert(pblock-&gt;vtx[0].vin[0].scriptSig.size() &lt;= 100);</p>
<p style="Normal" xid="3561"><c></c></p>
<p style="Normal" xid="3562" props="text-align:left; dom-dir:ltr">    pblock-&gt;hashMerkleRoot = pblock-&gt;BuildMerkleTree();</p>
<p style="Normal" xid="3563">}</p>
<p style="Normal" xid="3564"><c></c></p>
<p style="Normal" xid="3565"><c></c></p>
<p style="Normal" xid="3566" props="text-align:left; dom-dir:ltr">void FormatHashBuffers(CBlock* pblock, char* pmidstate, char* pdata, char* phash1)</p>
<p style="Normal" xid="3567">{</p>
<p style="Normal" xid="3568">    //</p>
<p style="Normal" xid="3569" props="text-align:left; dom-dir:ltr">    // Prebuild hash buffers</p>
<p style="Normal" xid="3570">    //</p>
<p style="Normal" xid="3571" props="text-align:left; dom-dir:ltr">    struct</p>
<p style="Normal" xid="3572">    {</p>
<p style="Normal" xid="3573" props="text-align:left; dom-dir:ltr">        struct unnamed2</p>
<p style="Normal" xid="3574">        {</p>
<p style="Normal" xid="3575" props="text-align:left; dom-dir:ltr">            int nVersion;</p>
<p style="Normal" xid="3576" props="text-align:left; dom-dir:ltr">            uint256 hashPrevBlock;</p>
<p style="Normal" xid="3577" props="text-align:left; dom-dir:ltr">            uint256 hashMerkleRoot;</p>
<p style="Normal" xid="3578" props="text-align:left; dom-dir:ltr">            unsigned int nTime;</p>
<p style="Normal" xid="3579" props="text-align:left; dom-dir:ltr">            unsigned int nBits;</p>
<p style="Normal" xid="3580" props="text-align:left; dom-dir:ltr">            unsigned int nNonce;</p>
<p style="Normal" xid="3581">        }</p>
<p style="Normal" xid="3582" props="text-align:left; dom-dir:ltr">        block;</p>
<p style="Normal" xid="3583" props="text-align:left; dom-dir:ltr">        unsigned char pchPadding0[64];</p>
<p style="Normal" xid="3584" props="text-align:left; dom-dir:ltr">        uint256 hash1;</p>
<p style="Normal" xid="3585" props="text-align:left; dom-dir:ltr">        unsigned char pchPadding1[64];</p>
<p style="Normal" xid="3586">    }</p>
<p style="Normal" xid="3587" props="text-align:left; dom-dir:ltr">    tmp;</p>
<p style="Normal" xid="3588" props="text-align:left; dom-dir:ltr">    memset(&amp;tmp, 0, sizeof(tmp));</p>
<p style="Normal" xid="3589"><c></c></p>
<p style="Normal" xid="3590" props="text-align:left; dom-dir:ltr">    tmp.block.nVersion       = pblock-&gt;nVersion;</p>
<p style="Normal" xid="3591" props="text-align:left; dom-dir:ltr">    tmp.block.hashPrevBlock  = pblock-&gt;hashPrevBlock;</p>
<p style="Normal" xid="3592" props="text-align:left; dom-dir:ltr">    tmp.block.hashMerkleRoot = pblock-&gt;hashMerkleRoot;</p>
<p style="Normal" xid="3593" props="text-align:left; dom-dir:ltr">    tmp.block.nTime          = pblock-&gt;nTime;</p>
<p style="Normal" xid="3594" props="text-align:left; dom-dir:ltr">    tmp.block.nBits          = pblock-&gt;nBits;</p>
<p style="Normal" xid="3595" props="text-align:left; dom-dir:ltr">    tmp.block.nNonce         = pblock-&gt;nNonce;</p>
<p style="Normal" xid="3596"><c></c></p>
<p style="Normal" xid="3597" props="text-align:left; dom-dir:ltr">    FormatHashBlocks(&amp;tmp.block, sizeof(tmp.block));</p>
<p style="Normal" xid="3598" props="text-align:left; dom-dir:ltr">    FormatHashBlocks(&amp;tmp.hash1, sizeof(tmp.hash1));</p>
<p style="Normal" xid="3599"><c></c></p>
<p style="Normal" xid="3600" props="text-align:left; dom-dir:ltr">    // Byte swap all the input buffer</p>
<p style="Normal" xid="3601" props="text-align:left; dom-dir:ltr">    for (unsigned int i = 0; i &lt; sizeof(tmp)/4; i++)</p>
<p style="Normal" xid="3602" props="text-align:left; dom-dir:ltr">        ((unsigned int*)&amp;tmp)[i] = ByteReverse(((unsigned int*)&amp;tmp)[i]);</p>
<p style="Normal" xid="3603"><c></c></p>
<p style="Normal" xid="3604" props="text-align:left; dom-dir:ltr">    // Precalc the first half of the first hash, which stays constant</p>
<p style="Normal" xid="3605" props="text-align:left; dom-dir:ltr">    SHA256Transform(pmidstate, &amp;tmp.block, pSHA256InitState);</p>
<p style="Normal" xid="3606"><c></c></p>
<p style="Normal" xid="3607" props="text-align:left; dom-dir:ltr">    memcpy(pdata, &amp;tmp.block, 128);</p>
<p style="Normal" xid="3608" props="text-align:left; dom-dir:ltr">    memcpy(phash1, &amp;tmp.hash1, 64);</p>
<p style="Normal" xid="3609">}</p>
<p style="Normal" xid="3610"><c></c></p>
<p style="Normal" xid="3611"><c></c></p>
<p style="Normal" xid="3612" props="text-align:left; dom-dir:ltr">bool CheckWork(CBlock* pblock, CWallet&amp; wallet, CReserveKey&amp; reservekey)</p>
<p style="Normal" xid="3613">{</p>
<p style="Normal" xid="3614" props="text-align:left; dom-dir:ltr">    uint256 hash = pblock-&gt;GetPoWHash();</p>
<p style="Normal" xid="3615" props="text-align:left; dom-dir:ltr">    uint256 hashTarget = CBigNum().SetCompact(pblock-&gt;nBits).getuint256();</p>
<p style="Normal" xid="3616"><c></c></p>
<p style="Normal" xid="3617" props="text-align:left; dom-dir:ltr">    if (hash &gt; hashTarget)</p>
<p style="Normal" xid="3618" props="text-align:left; dom-dir:ltr">        return false;</p>
<p style="Normal" xid="3619"><c></c></p>
<p style="Normal" xid="3620" props="text-align:left; dom-dir:ltr">    //// debug print</p>
<p style="Normal" xid="3621" props="text-align:left; dom-dir:ltr">    printf("BitcoinMiner:\n");</p>
<p style="Normal" xid="3622" props="text-align:left; dom-dir:ltr">    printf("proof-of-work found  \n  hash: %s  \ntarget: %s\n", hash.GetHex().c_str(), hashTarget.GetHex().c_str());</p>
<p style="Normal" xid="3623" props="text-align:left; dom-dir:ltr">    pblock-&gt;print();</p>
<p style="Normal" xid="3624" props="text-align:left; dom-dir:ltr">    printf("generated %s\n", FormatMoney(pblock-&gt;vtx[0].vout[0].nValue).c_str());</p>
<p style="Normal" xid="3625"><c></c></p>
<p style="Normal" xid="3626" props="text-align:left; dom-dir:ltr">    // Found a solution</p>
<p style="Normal" xid="3627">    {</p>
<p style="Normal" xid="3628" props="text-align:left; dom-dir:ltr">        LOCK(cs_main);</p>
<p style="Normal" xid="3629" props="text-align:left; dom-dir:ltr">        if (pblock-&gt;hashPrevBlock != hashBestChain)</p>
<p style="Normal" xid="3630" props="text-align:left; dom-dir:ltr">            return error("BitcoinMiner : generated block is stale");</p>
<p style="Normal" xid="3631"><c></c></p>
<p style="Normal" xid="3632" props="text-align:left; dom-dir:ltr">        // Remove key from key pool</p>
<p style="Normal" xid="3633" props="text-align:left; dom-dir:ltr">        reservekey.KeepKey();</p>
<p style="Normal" xid="3634"><c></c></p>
<p style="Normal" xid="3635" props="text-align:left; dom-dir:ltr">        // Track how many getdata requests this block gets</p>
<p style="Normal" xid="3636">        {</p>
<p style="Normal" xid="3637" props="text-align:left; dom-dir:ltr">            LOCK(wallet.cs_wallet);</p>
<p style="Normal" xid="3638" props="text-align:left; dom-dir:ltr">            wallet.mapRequestCount[pblock-&gt;GetHash()] = 0;</p>
<p style="Normal" xid="3639">        }</p>
<p style="Normal" xid="3640"><c></c></p>
<p style="Normal" xid="3641" props="text-align:left; dom-dir:ltr">        // Process this block the same as if we had received it from another node</p>
<p style="Normal" xid="3642" props="text-align:left; dom-dir:ltr">        if (!ProcessBlock(NULL, pblock))</p>
<p style="Normal" xid="3643" props="text-align:left; dom-dir:ltr">            return error("BitcoinMiner : ProcessBlock, block not accepted");</p>
<p style="Normal" xid="3644">    }</p>
<p style="Normal" xid="3645"><c></c></p>
<p style="Normal" xid="3646" props="text-align:left; dom-dir:ltr">    return true;</p>
<p style="Normal" xid="3647">}</p>
<p style="Normal" xid="3648"><c></c></p>
<p style="Normal" xid="3649" props="text-align:left; dom-dir:ltr">void static ThreadBitcoinMiner(void* parg);</p>
<p style="Normal" xid="3650"><c></c></p>
<p style="Normal" xid="3651" props="text-align:left; dom-dir:ltr">static bool fGenerateBitcoins = false;</p>
<p style="Normal" xid="3652" props="text-align:left; dom-dir:ltr">static bool fLimitProcessors = false;</p>
<p style="Normal" xid="3653" props="text-align:left; dom-dir:ltr">static int nLimitProcessors = -1;</p>
<p style="Normal" xid="3654"><c></c></p>
<p style="Normal" xid="3655" props="text-align:left; dom-dir:ltr">void static BitcoinMiner(CWallet *pwallet)</p>
<p style="Normal" xid="3656">{</p>
<p style="Normal" xid="3657" props="text-align:left; dom-dir:ltr">    printf("BitcoinMiner started\n");</p>
<p style="Normal" xid="3658" props="text-align:left; dom-dir:ltr">    SetThreadPriority(THREAD_PRIORITY_LOWEST);</p>
<p style="Normal" xid="3659"><c></c></p>
<p style="Normal" xid="3660" props="text-align:left; dom-dir:ltr">    // Make this thread recognisable as the mining thread</p>
<p style="Normal" xid="3661" props="text-align:left; dom-dir:ltr">    RenameThread("bitcoin-miner");</p>
<p style="Normal" xid="3662"><c></c></p>
<p style="Normal" xid="3663" props="text-align:left; dom-dir:ltr">    // Each thread has its own key and counter</p>
<p style="Normal" xid="3664" props="text-align:left; dom-dir:ltr">    CReserveKey reservekey(pwallet);</p>
<p style="Normal" xid="3665" props="text-align:left; dom-dir:ltr">    unsigned int nExtraNonce = 0;</p>
<p style="Normal" xid="3666"><c></c></p>
<p style="Normal" xid="3667" props="text-align:left; dom-dir:ltr">    while (fGenerateBitcoins)</p>
<p style="Normal" xid="3668">    {</p>
<p style="Normal" xid="3669" props="text-align:left; dom-dir:ltr">        if (fShutdown)</p>
<p style="Normal" xid="3670" props="text-align:left; dom-dir:ltr">            return;</p>
<p style="Normal" xid="3671" props="text-align:left; dom-dir:ltr">        while (vNodes.empty() || IsInitialBlockDownload())</p>
<p style="Normal" xid="3672">        {</p>
<p style="Normal" xid="3673" props="text-align:left; dom-dir:ltr">            Sleep(1000);</p>
<p style="Normal" xid="3674" props="text-align:left; dom-dir:ltr">            if (fShutdown)</p>
<p style="Normal" xid="3675" props="text-align:left; dom-dir:ltr">                return;</p>
<p style="Normal" xid="3676" props="text-align:left; dom-dir:ltr">            if (!fGenerateBitcoins)</p>
<p style="Normal" xid="3677" props="text-align:left; dom-dir:ltr">                return;</p>
<p style="Normal" xid="3678">        }</p>
<p style="Normal" xid="3679"><c></c></p>
<p style="Normal" xid="3680"><c></c></p>
<p style="Normal" xid="3681">        //</p>
<p style="Normal" xid="3682" props="text-align:left; dom-dir:ltr">        // Create new block</p>
<p style="Normal" xid="3683">        //</p>
<p style="Normal" xid="3684" props="text-align:left; dom-dir:ltr">        unsigned int nTransactionsUpdatedLast = nTransactionsUpdated;</p>
<p style="Normal" xid="3685" props="text-align:left; dom-dir:ltr">        CBlockIndex* pindexPrev = pindexBest;</p>
<p style="Normal" xid="3686"><c></c></p>
<p style="Normal" xid="3687" props="text-align:left; dom-dir:ltr">        auto_ptr&lt;CBlock&gt; pblock(CreateNewBlock(reservekey));</p>
<p style="Normal" xid="3688" props="text-align:left; dom-dir:ltr">        if (!pblock.get())</p>
<p style="Normal" xid="3689" props="text-align:left; dom-dir:ltr">            return;</p>
<p style="Normal" xid="3690" props="text-align:left; dom-dir:ltr">        IncrementExtraNonce(pblock.get(), pindexPrev, nExtraNonce);</p>
<p style="Normal" xid="3691"><c></c></p>
<p style="Normal" xid="3692" props="text-align:left; dom-dir:ltr">        printf("Running BitcoinMiner with %d transactions in block\n", pblock-&gt;vtx.size());</p>
<p style="Normal" xid="3693"><c></c></p>
<p style="Normal" xid="3694"><c></c></p>
<p style="Normal" xid="3695">        //</p>
<p style="Normal" xid="3696" props="text-align:left; dom-dir:ltr">        // Prebuild hash buffers</p>
<p style="Normal" xid="3697">        //</p>
<p style="Normal" xid="3698" props="text-align:left; dom-dir:ltr">        char pmidstatebuf[32+16]; char* pmidstate = alignup&lt;16&gt;(pmidstatebuf);</p>
<p style="Normal" xid="3699" props="text-align:left; dom-dir:ltr">        char pdatabuf[128+16];    char* pdata     = alignup&lt;16&gt;(pdatabuf);</p>
<p style="Normal" xid="3700" props="text-align:left; dom-dir:ltr">        char phash1buf[64+16];    char* phash1    = alignup&lt;16&gt;(phash1buf);</p>
<p style="Normal" xid="3701"><c></c></p>
<p style="Normal" xid="3702" props="text-align:left; dom-dir:ltr">        FormatHashBuffers(pblock.get(), pmidstate, pdata, phash1);</p>
<p style="Normal" xid="3703"><c></c></p>
<p style="Normal" xid="3704" props="text-align:left; dom-dir:ltr">        unsigned int&amp; nBlockTime = *(unsigned int*)(pdata + 64 + 4);</p>
<p style="Normal" xid="3705" props="text-align:left; dom-dir:ltr">        unsigned int&amp; nBlockBits = *(unsigned int*)(pdata + 64 + 8);</p>
<p style="Normal" xid="3706" props="text-align:left; dom-dir:ltr">        //unsigned int&amp; nBlockNonce = *(unsigned int*)(pdata + 64 + 12);</p>
<p style="Normal" xid="3707"><c></c></p>
<p style="Normal" xid="3708"><c></c></p>
<p style="Normal" xid="3709">        //</p>
<p style="Normal" xid="3710" props="text-align:left; dom-dir:ltr">        // Search</p>
<p style="Normal" xid="3711">        //</p>
<p style="Normal" xid="3712" props="text-align:left; dom-dir:ltr">        int64 nStart = GetTime();</p>
<p style="Normal" xid="3713" props="text-align:left; dom-dir:ltr">        uint256 hashTarget = CBigNum().SetCompact(pblock-&gt;nBits).getuint256();</p>
<p style="Normal" xid="3714" props="text-align:left; dom-dir:ltr">        loop</p>
<p style="Normal" xid="3715">        {</p>
<p style="Normal" xid="3716" props="text-align:left; dom-dir:ltr">            unsigned int nHashesDone = 0;</p>
<p style="Normal" xid="3717" props="text-align:left; dom-dir:ltr">            //unsigned int nNonceFound;</p>
<p style="Normal" xid="3718"><c></c></p>
<p style="Normal" xid="3719" props="text-align:left; dom-dir:ltr">            uint256 thash;</p>
<p style="Normal" xid="3720" props="text-align:left; dom-dir:ltr">            char scratchpad[SCRYPT_SCRATCHPAD_SIZE];</p>
<p style="Normal" xid="3721" props="text-align:left; dom-dir:ltr">            loop</p>
<p style="Normal" xid="3722">            {</p>
<p style="Normal" xid="3723" props="text-align:left; dom-dir:ltr">                scrypt_1024_1_1_256_sp(BEGIN(pblock-&gt;nVersion), BEGIN(thash), scratchpad);</p>
<p style="Normal" xid="3724"><c></c></p>
<p style="Normal" xid="3725" props="text-align:left; dom-dir:ltr">                if (thash &lt;= hashTarget)</p>
<p style="Normal" xid="3726">                {</p>
<p style="Normal" xid="3727" props="text-align:left; dom-dir:ltr">                    // Found a solution</p>
<p style="Normal" xid="3728" props="text-align:left; dom-dir:ltr">                    SetThreadPriority(THREAD_PRIORITY_NORMAL);</p>
<p style="Normal" xid="3729" props="text-align:left; dom-dir:ltr">                    CheckWork(pblock.get(), *pwalletMain, reservekey);</p>
<p style="Normal" xid="3730" props="text-align:left; dom-dir:ltr">                    SetThreadPriority(THREAD_PRIORITY_LOWEST);</p>
<p style="Normal" xid="3731" props="text-align:left; dom-dir:ltr">                    break;</p>
<p style="Normal" xid="3732">                }</p>
<p style="Normal" xid="3733" props="text-align:left; dom-dir:ltr">                pblock-&gt;nNonce += 1;</p>
<p style="Normal" xid="3734" props="text-align:left; dom-dir:ltr">                nHashesDone += 1;</p>
<p style="Normal" xid="3735" props="text-align:left; dom-dir:ltr">                if ((pblock-&gt;nNonce &amp; 0xFF) == 0)</p>
<p style="Normal" xid="3736" props="text-align:left; dom-dir:ltr">                    break;</p>
<p style="Normal" xid="3737">            }</p>
<p style="Normal" xid="3738"><c></c></p>
<p style="Normal" xid="3739" props="text-align:left; dom-dir:ltr">            // Meter hashes/sec</p>
<p style="Normal" xid="3740" props="text-align:left; dom-dir:ltr">            static int64 nHashCounter;</p>
<p style="Normal" xid="3741" props="text-align:left; dom-dir:ltr">            if (nHPSTimerStart == 0)</p>
<p style="Normal" xid="3742">            {</p>
<p style="Normal" xid="3743" props="text-align:left; dom-dir:ltr">                nHPSTimerStart = GetTimeMillis();</p>
<p style="Normal" xid="3744" props="text-align:left; dom-dir:ltr">                nHashCounter = 0;</p>
<p style="Normal" xid="3745">            }</p>
<p style="Normal" xid="3746" props="text-align:left; dom-dir:ltr">            else</p>
<p style="Normal" xid="3747" props="text-align:left; dom-dir:ltr">                nHashCounter += nHashesDone;</p>
<p style="Normal" xid="3748" props="text-align:left; dom-dir:ltr">            if (GetTimeMillis() - nHPSTimerStart &gt; 4000)</p>
<p style="Normal" xid="3749">            {</p>
<p style="Normal" xid="3750" props="text-align:left; dom-dir:ltr">                static CCriticalSection cs;</p>
<p style="Normal" xid="3751">                {</p>
<p style="Normal" xid="3752" props="text-align:left; dom-dir:ltr">                    LOCK(cs);</p>
<p style="Normal" xid="3753" props="text-align:left; dom-dir:ltr">                    if (GetTimeMillis() - nHPSTimerStart &gt; 4000)</p>
<p style="Normal" xid="3754">                    {</p>
<p style="Normal" xid="3755" props="text-align:left; dom-dir:ltr">                        dHashesPerSec = 1000.0 * nHashCounter / (GetTimeMillis() - nHPSTimerStart);</p>
<p style="Normal" xid="3756" props="text-align:left; dom-dir:ltr">                        nHPSTimerStart = GetTimeMillis();</p>
<p style="Normal" xid="3757" props="text-align:left; dom-dir:ltr">                        nHashCounter = 0;</p>
<p style="Normal" xid="3758" props="text-align:left; dom-dir:ltr">                        string strStatus = strprintf("    %.0f khash/s", dHashesPerSec/1000.0);</p>
<p style="Normal" xid="3759" props="text-align:left; dom-dir:ltr">                        static int64 nLogTime;</p>
<p style="Normal" xid="3760" props="text-align:left; dom-dir:ltr">                        if (GetTime() - nLogTime &gt; 30 * 60)</p>
<p style="Normal" xid="3761">                        {</p>
<p style="Normal" xid="3762" props="text-align:left; dom-dir:ltr">                            nLogTime = GetTime();</p>
<p style="Normal" xid="3763" props="text-align:left; dom-dir:ltr">                            printf("%s ", DateTimeStrFormat("%x %H:%M", GetTime()).c_str());</p>
<p style="Normal" xid="3764" props="text-align:left; dom-dir:ltr">                            printf("hashmeter %3d CPUs %6.0f khash/s\n", vnThreadsRunning[THREAD_MINER], dHashesPerSec/1000.0);</p>
<p style="Normal" xid="3765">                        }</p>
<p style="Normal" xid="3766">                    }</p>
<p style="Normal" xid="3767">                }</p>
<p style="Normal" xid="3768">            }</p>
<p style="Normal" xid="3769"><c></c></p>
<p style="Normal" xid="3770" props="text-align:left; dom-dir:ltr">            // Check for stop or if block needs to be rebuilt</p>
<p style="Normal" xid="3771" props="text-align:left; dom-dir:ltr">            if (fShutdown)</p>
<p style="Normal" xid="3772" props="text-align:left; dom-dir:ltr">                return;</p>
<p style="Normal" xid="3773" props="text-align:left; dom-dir:ltr">            if (!fGenerateBitcoins)</p>
<p style="Normal" xid="3774" props="text-align:left; dom-dir:ltr">                return;</p>
<p style="Normal" xid="3775" props="text-align:left; dom-dir:ltr">            if (fLimitProcessors &amp;&amp; vnThreadsRunning[THREAD_MINER] &gt; nLimitProcessors)</p>
<p style="Normal" xid="3776" props="text-align:left; dom-dir:ltr">                return;</p>
<p style="Normal" xid="3777" props="text-align:left; dom-dir:ltr">            if (vNodes.empty())</p>
<p style="Normal" xid="3778" props="text-align:left; dom-dir:ltr">                break;</p>
<p style="Normal" xid="3779" props="text-align:left; dom-dir:ltr">            if (pblock-&gt;nNonce &gt;= 0xffff0000)</p>
<p style="Normal" xid="3780" props="text-align:left; dom-dir:ltr">                break;</p>
<p style="Normal" xid="3781" props="text-align:left; dom-dir:ltr">            if (nTransactionsUpdated != nTransactionsUpdatedLast &amp;&amp; GetTime() - nStart &gt; 60)</p>
<p style="Normal" xid="3782" props="text-align:left; dom-dir:ltr">                break;</p>
<p style="Normal" xid="3783" props="text-align:left; dom-dir:ltr">            if (pindexPrev != pindexBest)</p>
<p style="Normal" xid="3784" props="text-align:left; dom-dir:ltr">                break;</p>
<p style="Normal" xid="3785"><c></c></p>
<p style="Normal" xid="3786" props="text-align:left; dom-dir:ltr">            // Update nTime every few seconds</p>
<p style="Normal" xid="3787" props="text-align:left; dom-dir:ltr">            pblock-&gt;UpdateTime(pindexPrev);</p>
<p style="Normal" xid="3788" props="text-align:left; dom-dir:ltr">            nBlockTime = ByteReverse(pblock-&gt;nTime);</p>
<p style="Normal" xid="3789" props="text-align:left; dom-dir:ltr">            if (fTestNet)</p>
<p style="Normal" xid="3790">            {</p>
<p style="Normal" xid="3791" props="text-align:left; dom-dir:ltr">                // Changing pblock-&gt;nTime can change work required on testnet:</p>
<p style="Normal" xid="3792" props="text-align:left; dom-dir:ltr">                nBlockBits = ByteReverse(pblock-&gt;nBits);</p>
<p style="Normal" xid="3793" props="text-align:left; dom-dir:ltr">                hashTarget = CBigNum().SetCompact(pblock-&gt;nBits).getuint256();</p>
<p style="Normal" xid="3794">            }</p>
<p style="Normal" xid="3795">        }</p>
<p style="Normal" xid="3796">    }</p>
<p style="Normal" xid="3797">}</p>
<p style="Normal" xid="3798"><c></c></p>
<p style="Normal" xid="3799" props="text-align:left; dom-dir:ltr">void static ThreadBitcoinMiner(void* parg)</p>
<p style="Normal" xid="3800">{</p>
<p style="Normal" xid="3801" props="text-align:left; dom-dir:ltr">    CWallet* pwallet = (CWallet*)parg;</p>
<p style="Normal" xid="3802" props="text-align:left; dom-dir:ltr">    try</p>
<p style="Normal" xid="3803">    {</p>
<p style="Normal" xid="3804" props="text-align:left; dom-dir:ltr">        vnThreadsRunning[THREAD_MINER]++;</p>
<p style="Normal" xid="3805" props="text-align:left; dom-dir:ltr">        BitcoinMiner(pwallet);</p>
<p style="Normal" xid="3806" props="text-align:left; dom-dir:ltr">        vnThreadsRunning[THREAD_MINER]--;</p>
<p style="Normal" xid="3807">    }</p>
<p style="Normal" xid="3808" props="text-align:left; dom-dir:ltr">    catch (std::exception&amp; e) {</p>
<p style="Normal" xid="3809" props="text-align:left; dom-dir:ltr">        vnThreadsRunning[THREAD_MINER]--;</p>
<p style="Normal" xid="3810" props="text-align:left; dom-dir:ltr">        PrintException(&amp;e, "ThreadBitcoinMiner()");</p>
<p style="Normal" xid="3811" props="text-align:left; dom-dir:ltr">    } catch (...) {</p>
<p style="Normal" xid="3812" props="text-align:left; dom-dir:ltr">        vnThreadsRunning[THREAD_MINER]--;</p>
<p style="Normal" xid="3813" props="text-align:left; dom-dir:ltr">        PrintException(NULL, "ThreadBitcoinMiner()");</p>
<p style="Normal" xid="3814">    }</p>
<p style="Normal" xid="3815" props="text-align:left; dom-dir:ltr">    nHPSTimerStart = 0;</p>
<p style="Normal" xid="3816" props="text-align:left; dom-dir:ltr">    if (vnThreadsRunning[THREAD_MINER] == 0)</p>
<p style="Normal" xid="3817" props="text-align:left; dom-dir:ltr">        dHashesPerSec = 0;</p>
<p style="Normal" xid="3818" props="text-align:left; dom-dir:ltr">    printf("ThreadBitcoinMiner exiting, %d threads remaining\n", vnThreadsRunning[THREAD_MINER]);</p>
<p style="Normal" xid="3819">}</p>
<p style="Normal" xid="3820"><c></c></p>
<p style="Normal" xid="3821"><c></c></p>
<p style="Normal" xid="3822" props="text-align:left; dom-dir:ltr">void GenerateBitcoins(bool fGenerate, CWallet* pwallet)</p>
<p style="Normal" xid="3823">{</p>
<p style="Normal" xid="3824" props="text-align:left; dom-dir:ltr">    fGenerateBitcoins = fGenerate;</p>
<p style="Normal" xid="3825" props="text-align:left; dom-dir:ltr">    nLimitProcessors = GetArg("-genproclimit", -1);</p>
<p style="Normal" xid="3826" props="text-align:left; dom-dir:ltr">    if (nLimitProcessors == 0)</p>
<p style="Normal" xid="3827" props="text-align:left; dom-dir:ltr">        fGenerateBitcoins = false;</p>
<p style="Normal" xid="3828" props="text-align:left; dom-dir:ltr">    fLimitProcessors = (nLimitProcessors != -1);</p>
<p style="Normal" xid="3829"><c></c></p>
<p style="Normal" xid="3830" props="text-align:left; dom-dir:ltr">    if (fGenerate)</p>
<p style="Normal" xid="3831">    {</p>
<p style="Normal" xid="3832" props="text-align:left; dom-dir:ltr">        int nProcessors = boost::thread::hardware_concurrency();</p>
<p style="Normal" xid="3833" props="text-align:left; dom-dir:ltr">        printf("%d processors\n", nProcessors);</p>
<p style="Normal" xid="3834" props="text-align:left; dom-dir:ltr">        if (nProcessors &lt; 1)</p>
<p style="Normal" xid="3835" props="text-align:left; dom-dir:ltr">            nProcessors = 1;</p>
<p style="Normal" xid="3836" props="text-align:left; dom-dir:ltr">        if (fLimitProcessors &amp;&amp; nProcessors &gt; nLimitProcessors)</p>
<p style="Normal" xid="3837" props="text-align:left; dom-dir:ltr">            nProcessors = nLimitProcessors;</p>
<p style="Normal" xid="3838" props="text-align:left; dom-dir:ltr">        int nAddThreads = nProcessors - vnThreadsRunning[THREAD_MINER];</p>
<p style="Normal" xid="3839" props="text-align:left; dom-dir:ltr">        printf("Starting %d BitcoinMiner threads\n", nAddThreads);</p>
<p style="Normal" xid="3840" props="text-align:left; dom-dir:ltr">        for (int i = 0; i &lt; nAddThreads; i++)</p>
<p style="Normal" xid="3841">        {</p>
<p style="Normal" xid="3842" props="text-align:left; dom-dir:ltr">            if (!CreateThread(ThreadBitcoinMiner, pwallet))</p>
<p style="Normal" xid="3843" props="text-align:left; dom-dir:ltr">                printf("Error: CreateThread(ThreadBitcoinMiner) failed\n");</p>
<p style="Normal" xid="3844" props="text-align:left; dom-dir:ltr">            Sleep(10);</p>
<p style="Normal" xid="3845">        }</p>
<p style="Normal" xid="3846">    }</p>
<p style="Normal" xid="3847">}</p>
<p style="Normal" xid="3848"></p>
</section>
</abiword>
