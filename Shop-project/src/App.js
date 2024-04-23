import React from 'react';
import './style.css';
import { createBrowserRouter, RouterProvider } from 'react-router-dom';
import { Home } from './pages/Home';
import { Cart } from './pages/Cart';
import { Products } from './pages/Products';
import { Product } from './pages/Product';
import { Favorites } from './pages/Favorites';
import { Header } from './components/Header';
import { useReducer } from 'react';
import {
  initialState as cartInitialState,
  cartReducer,
} from './store/Cart/reducer';
import { CartContext } from './store/Cart/context';
import {
  initialFavoritesState,
  favoritesReducer,
} from './store/Favorites/reducer';
import { FavoritesContext } from './store/Favorites/context';
import {
  initialState as themeInitialState,
  themeReducer,
} from './store/Theme/reducer';
import { ThemeContext } from './store/Theme/context';

const router = createBrowserRouter([
  {
    path: '/',
    element: (
      <>
        <Header />
        <Home />
      </>
    ),
  },
  {
    path: '/products',
    element: (
      <>
        <Header />
        <Products />
      </>
    ),
  },
  {
    path: '/product/:id',
    element: (
      <>
        <Header />
        <Product />
      </>
    ),
  },
  {
    path: '/cart',
    element: (
      <>
        <Header />
        <Cart />
      </>
    ),
  },
  {
    path: '/favorites',
    element: (
      <>
        <Header />
        <Favorites />
      </>
    ),
  },
]);

export default function App() {
  const [cartState, cartDispatch] = useReducer(cartReducer, cartInitialState);
  const [favoritesState, favoritesDispatch] = useReducer(
    favoritesReducer,
    initialFavoritesState
  );
  const [themeState, themeDispatch] = useReducer(
    themeReducer,
    themeInitialState
  );

  const cartContextValue = {
    state: cartState,
    dispatch: cartDispatch,
  };

  const favoritesContextValue = {
    state: favoritesState,
    dispatch: favoritesDispatch,
  };

  const themeContextValue = {
    themeState,
    themeDispatch,
  };

  return (
    <CartContext.Provider value={cartContextValue}>
      <FavoritesContext.Provider value={favoritesContextValue}>
        <ThemeContext.Provider value={themeContextValue}>
          <div className="App primary">
            <RouterProvider router={router} />
          </div>
        </ThemeContext.Provider>
      </FavoritesContext.Provider>
    </CartContext.Provider>
  );
}
