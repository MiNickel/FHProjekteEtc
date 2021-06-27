using Newtonsoft.Json.Linq;
using SGSE.Models;
using SGSE.Repositories;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

namespace SGSE.Services
{
    public class InvoiceService : IInvoiceService
    {
        private readonly IInvoiceRepository _repository;
        private readonly HttpClient _client;

        public InvoiceService(IInvoiceRepository repository)
        {
            _repository = repository;
            _client = new HttpClient();
        }
        public Task<Invoice> Create(Invoice invoice)
        {
            var access_token = GetPaypalAccessToken();
            //var createdInvoice = _repository.Create(invoice);

            throw new NotImplementedException();
        }

        public Task<List<Invoice>> GetAll()
        {
            throw new NotImplementedException();
        }

        public Task<Invoice> GetById(string id)
        {
            throw new NotImplementedException();
        }

        public string GetPaypalAccessToken()
        {
            WebRequest request = WebRequest.Create("https://api-m.sandbox.paypal.com/v1/oauth2/token");
            request.Method = "POST";
            var username = "ASchRjlk4vOH0uRd5BwQ3Lt408sw_7wydEShg63KSyxkA5tVrIWRyJhSWZc8Ig8TFXRVRVEan3d6Ufe4";
            var password = "EPzvTyrJLKDOdyUwNh18IHA03vC8-55IM-hqoirJ9uIOu8_dFQrD_AaglbTOs70k9LUPv353Dll4h75f";
            string encoded = Convert.ToBase64String(Encoding.GetEncoding("ISO-8859-1")
                                           .GetBytes(username + ":" + password));
            request.Headers.Add("Authorization", "Basic " + encoded);
            request.Headers.Add("Accept", "application/json");
            request.ContentType = "application/x-www-form-urlencoded";
            string postData = "grant_type=client_credentials";
            byte[] byteArray = Encoding.UTF8.GetBytes(postData);
            request.ContentLength = byteArray.Length;
            // Get the request stream.
            Stream dataStream = request.GetRequestStream();
            // Write the data to the request stream.
            dataStream.Write(byteArray, 0, byteArray.Length);
            // Close the Stream object.
            dataStream.Close();
            // Get the response.
            WebResponse response = request.GetResponse();
            // Display the status.
            // Get the stream associated with the response.
            Stream receiveStream = response.GetResponseStream();
            // Pipes the stream to a higher level stream reader with the required encoding format.
            StreamReader readStream = new(receiveStream, Encoding.UTF8);
            var res = readStream.ReadToEnd();
            readStream.Close();
            receiveStream.Close();
            response.Close();
            JObject json = JObject.Parse(res);
            return (string) json["access_token"];
        }

        public Task Remove(Invoice invoice)
        {
            throw new NotImplementedException();
        }

        public Task RemoveById(string id)
        {
            throw new NotImplementedException();
        }

        public Task Update(string id, Invoice invoice)
        {
            throw new NotImplementedException();
        }
    }
}
